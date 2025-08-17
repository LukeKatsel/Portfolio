/* ------------------------------------------------------------------------
   phase1.c

   CSCV 452

   ------------------------------------------------------------------------ */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <phase1.h>
#include "kernel.h"

#ifndef NULL
#define NULL ((void*)0)
#endif

/* ------------------------- Prototypes ----------------------------------- */
int sentinel (char *);
extern int start1 (char *);
void dispatcher(void);
void launch();
static void enableInterrupts();
static void check_deadlock();
proc_ptr GetNextReadyProc();
int GetProcSlot();


/* -------------------------- Globals ------------------------------------- */

/* Patrick's debugging global variable... */
int debugflag = 1;

/* the process table */
proc_struct ProcTable[MAXPROC];

/* Process lists  */

/* current process ID */
proc_ptr Current;

/* the next pid to be assigned */
unsigned int nextPid = SENTINELPID;

int readyToStart = 0;

//linked list of ready processes 
List ReadyList;


/* -------------------------- Functions ----------------------------------- */
/* ------------------------------------------------------------------------
   Name - startup
   Purpose - Initializes process lists and clock interrupt vector.
	     Start up sentinel process and the test process.
   Parameters - none, called by USLOSS
   Returns - nothing
   Side Effects - lots, starts the whole thing
   ----------------------------------------------------------------------- */
void startup()
{
   int i;      /* loop index */
   int result; /* value returned by call to fork1() */

   /* initialize the process table */
   if (DEBUG && debugflag)
      console("startup(): initializing the Ready & Blocked lists\n");

   List initList;

   initList.pHead = NULL;
   initList.pTail = NULL;
   initList.count = 0;
   initList.offset = 0;

   for (i = 0; i < MAXPROC; i++){

      ProcTable[i].parent_proc_ptr = NULL;
      ProcTable[i].children = initList;
      ProcTable[i].quittingChildren = initList;
      ProcTable[i].zappers = initList;
      strcpy(ProcTable[i].name, "");
      ProcTable[i].start_arg[0] = '\0';
      //ProcTable[i].state = 
      ProcTable[i].pid = -1;
      ProcTable[i].priority = -1;
      ProcTable[i].start_func = NULL;
      ProcTable[i].stack = NULL;
      ProcTable[i].stacksize = -1;
      ProcTable[i].status = STATUS_EMPTY;
      ProcTable[i].cputime = -1;
      ProcTable[i].result = -1;


   }

   /* Initialize the Ready list, etc. */
   ReadyList = initList;

   /* Initialize the clock interrupt handler */
   

   /* startup a sentinel process */
   if (DEBUG && debugflag)
       console("startup(): calling fork1() for sentinel\n");

   result = fork1("sentinel", sentinel, NULL, USLOSS_MIN_STACK, SENTINELPRIORITY);

   if (result < 0) {
      if (DEBUG && debugflag)
         console("startup(): fork1 of sentinel returned error, halting...\n");
      halt(1);
   }

   //indicate we are ready to dispatch
   readyToStart = 1;
  
   /* start the test process */
   if (DEBUG && debugflag)
      console("startup(): calling fork1() for start1\n");

   result = fork1("start1", start1, NULL, 2 * USLOSS_MIN_STACK, 1);

   if (result < 0) {
      console("startup(): fork1 for start1 returned an error, halting...\n");
      halt(1);
   }

   console("startup(): Should not see this message! ");
   console("Returned from fork1 call that created start1\n");

   return;
} /* startup */

/* ------------------------------------------------------------------------
   Name - finish
   Purpose - Required by USLOSS
   Parameters - none
   Returns - nothing
   Side Effects - none
   ----------------------------------------------------------------------- */
void finish()
{
   if (DEBUG && debugflag)
      console("in finish...\n");
} /* finish */

/* ------------------------------------------------------------------------
   Name - fork1
   Purpose - Gets a new process from the process table and initializes
             information of the process.  Updates information in the
             parent process to reflect this child process creation.
   Parameters - the process procedure address, the size of the stack and
                the priority to be assigned to the child process.
   Returns - the process id of the created child or -1 if no child could
             be created or if priority is not between max and min priority.
   Side Effects - ReadyList is changed, ProcTable is changed, Current
                  process information changed
   ------------------------------------------------------------------------ */
int fork1(char *name, int (*f)(char *), char *arg, int stacksize, int priority)
{
   int procSlot;

   if (DEBUG && debugflag)
      console("fork1(): creating process %s\n", name);

   /* test if in kernel mode; halt if in user mode */
   if ( (PSR_CURRENT_MODE & psr_get()) == 0 ) {
      //not in kernel mode
      console("fork1(): called while in user mode, by process %d. Halting...\n", Current->pid);
      halt(1);
    }

   /* Return if stack size is too small */
   if (stacksize < USLOSS_MIN_STACK){
      if (DEBUG && debugflag)
         console("Stack size too small\n");

      return -1;
   }
   /* Return if name is null */
   if (name == NULL){
      if (DEBUG && debugflag)
         console("No Name\n");

      return -1;
   }
   /* Return if f is Null */
   if (f == NULL){
      if (DEBUG && debugflag)
         console("No starting function \n");

      return -1;
   }
   /* check priority */
   if (priority > MINPRIORITY && strcmp("sentinel", name) != 0){
      if (DEBUG && debugflag)
         console("Priority too low \n");

      return -1;
   }
   if (priority < MAXPRIORITY){
      if (DEBUG && debugflag)
         console("Priority too high \n");

      return -1;
   }


   /* find an empty slot in the process table */
   procSlot = GetProcSlot();
  

   /* fill-in entry in process table */
   if ( strlen(name) >= (MAXNAME - 1) ) {
      console("fork1(): Process name is too long.  Halting...\n");
      halt(1);
   }
   // fill in name
   strcpy(ProcTable[procSlot].name, name);

   // fill in starting function
   ProcTable[procSlot].start_func = f;

   // check if arg is NULL
   if ( arg == NULL )
      ProcTable[procSlot].start_arg[0] = '\0';

   else if ( strlen(arg) >= (MAXARG - 1) ) {
      console("fork1(): argument too long.  Halting...\n");
      halt(1);
   }
   else
      strcpy(ProcTable[procSlot].start_arg, arg);

   
   //Allocate the stack
   ProcTable[procSlot].stacksize = stacksize;
   ProcTable[procSlot].stack = malloc(stacksize);
   ProcTable[procSlot].pid = nextPid;
   ProcTable[procSlot].priority = priority;
   ProcTable[procSlot].status = STATUS_READY;
   ProcTable[procSlot].cputime = -1;

   // increment the next pid
   nextPid++;

   /* Initialize context for this process, but use launch function pointer for
    * the initial value of the process's program counter (PC)
    */
   context_init(&(ProcTable[procSlot].state), psr_get(), ProcTable[procSlot].stack, ProcTable[procSlot].stacksize, launch);

   /* for future phase(s) */
   p1_fork(ProcTable[procSlot].pid);

   // Set parent process 
   if (strcmp("sentinel", name) == 0 || strcmp("start1", name) == 0) {
      // no parent
      ProcTable[procSlot].parent_proc_ptr = NULL;
   }
   else{
      ProcTable[procSlot].parent_proc_ptr = Current;
   }
   
   // TODO Change current's kid list
   // AddNodeToList function

   // TODO add process to ready list
   //AddToReadyList(&ProcTable[proc_slot]);

   // TODO 
   if(readyToStart){
      dispatcher();
   }

   //dispatcher();

   return ProcTable[procSlot].pid;

} /* fork1 */

/* ------------------------------------------------------------------------
   Name - launch
   Purpose - Dummy function to enable interrupts and launch a given process
             upon startup.
   Parameters - none
   Returns - nothing
   Side Effects - enable interrupts
   ------------------------------------------------------------------------ */
void launch()
{
   int result;

   if (DEBUG && debugflag)
      console("launch(): started\n");

   /* Enable interrupts */
   enableInterrupts();

   /* Call the function passed to fork1, and capture its return value */
   result = Current->start_func(Current->start_arg);

   if (DEBUG && debugflag)
      console("Process %d returned to launch\n", Current->pid);

   quit(result);

} /* launch */


/* ------------------------------------------------------------------------
   Name - join
   Purpose - Wait for a child process (if one has been forked) to quit.  If 
             one has already quit, don't wait.
   Parameters - a pointer to an int where the termination code of the 
                quitting process is to be stored.
   Returns - the process id of the quitting child joined on.
		-1 if the process was zapped in the join
		-2 if the process has no children
   Side Effects - If no child process has quit before join is called, the 
                  parent is removed from the ready list and blocked.
   ------------------------------------------------------------------------ */
int join(int *code)
{
   return 0;
} /* join */


/* ------------------------------------------------------------------------
   Name - quit
   Purpose - Stops the child process and notifies the parent of the death by
             putting child quit info on the parents child completion code
             list.
   Parameters - the code to return to the grieving parent
   Returns - nothing
   Side Effects - changes the parent of pid child completion status list.
   ------------------------------------------------------------------------ */
void quit(int code)
{
   p1_quit(Current->pid);

   // TODO notify parent that child quit
   // parent back to ready list + status to ready 
   //current need to terminate
   //call dispatcher


} /* quit */

// TODO: get the next ready proc 
proc_ptr GetNextReadyProc(){

   // pull next entry from ready list
   /*for(int i = 1; i <= SENTINELPRIORITY; i++){

      // if there is an entry for this priority, get the first one
      if (ReadyList[i] != NULL){

         PopList();

         return nextProc;
      }
   }*/

   // TODO cheating to use start 1
   return(&ProcTable[2]);
}

/* ------------------------------------------------------------------------
   Name - dispatcher
   Purpose - dispatches ready processes.  The process with the highest
             priority (the first on the ready list) is scheduled to
             run.  The old process is swapped out and the new process
             swapped in.
   Parameters - none
   Returns - nothing
   Side Effects - the context of the machine is changed
   ----------------------------------------------------------------------- */
void dispatcher(void){
   
   proc_ptr next_process;
   context *pPrevContext = NULL;

   //TODO figure out: p1_switch
   //p1_switch(Current->pid, next_process->pid);

   //find the next process to run
   next_process = GetNextReadyProc();

   //set the current process to the new proc
   Current = next_process;

   //TODO swap in the new process and out w/ old
                     //old             new
   context_switch(pPrevContext, &next_process->state);
   // very first time ^NULL    

} /* dispatcher */


/* ------------------------------------------------------------------------
   Name - sentinel
   Purpose - The purpose of the sentinel routine is two-fold.  One
             responsibility is to keep the system going when all other
	     processes are blocked.  The other is to detect and report
	     simple deadlock states.
   Parameters - none
   Returns - nothing
   Side Effects -  if system is in deadlock, print appropriate error
		   and halt.
   ----------------------------------------------------------------------- */
int sentinel (char * dummy)
{
   if (DEBUG && debugflag)
      console("sentinel(): called\n");
   while (1)
   {
      check_deadlock();
      waitint();
   }
} /* sentinel */


/* check to determine if deadlock has occurred... */
static void check_deadlock()
{
} /* check_deadlock */


/*
 * Disables the interrupts.
 */
void disableInterrupts()
{
  /* turn the interrupts OFF iff we are in kernel mode */
  if((PSR_CURRENT_MODE & psr_get()) == 0) {
    //not in kernel mode
    console("Kernel Error: Not in kernel mode, may not disable interrupts\n");
    halt(1);
  } else
    /* We ARE in kernel mode */
    psr_set( psr_get() & ~PSR_CURRENT_INT );
} /* disableInterrupts */

static void enableInterrupts(){


}
/* ------------------------------------------------------------------------
   Name - GetProcSlot
   Purpose - The purpose is to find the next open slot in the proc table
            to put the new proc in.
   Parameters - none
   Returns - the free slot or -1 if can't find empty spot;
   Side Effects -  none
   ----------------------------------------------------------------------- */
int GetProcSlot() {
   int procSlot = -1;
   int tempPid = nextPid;

   for (int i = tempPid % MAXPROC; i < MAXPROC || i < tempPid % MAXPROC; ++i) {
      if (ProcTable[i].status == STATUS_EMPTY) {
         procSlot = i;
         break;
      } 
      else {
         nextPid++;
      }
   }

   return procSlot;
}
