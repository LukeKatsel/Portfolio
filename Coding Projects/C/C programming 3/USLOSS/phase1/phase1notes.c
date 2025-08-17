/* ------------------------------------------------------------------------
   phase1.c

   CSCV 452

   ------------------------------------------------------------------------ */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <phase1.h>
#include "kernel.h"
#include "usloss.h"

#ifndef NULL
#define NULL ((void *)0)
#endif


/* ------------------------- Prototypes ----------------------------------- */
int sentinel (void *);
extern int start1 (char *);
void dispatcher(void);
void launch();
static void enableInterrupts();
void disableInterrupts();
static void check_deadlock();


/* -------------------------- Globals ------------------------------------- */

/* Patrick's debugging global variable... */
int debugflag = 0;

/* the process table */
static proc_struct ProcTable[MAXPROC];  //TODO

typedef struct list_entry{
   struct list_entry *pNext;
   struct list_entry *pPrev;
   int value;
} EntryStructure;



/* Process lists  - one list for each priority level*/
List readyProcs[6];

/* number of active processes*/
static int numProc;

/* current process ID */
proc_ptr Current;

/* the next pid to be assigned */
unsigned int nextPid = SENTINELPID;


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

   /* Initialize the Ready list, etc. */
   if (DEBUG && debugflag)
      console("startup(): initializing the Ready & Blocked lists\n");
   //ReadyList = NULL;

   /* Initialize the clock interrupt handler */

   /* startup a sentinel process */
   if (DEBUG && debugflag)
       console("startup(): calling fork1() for sentinel\n");
   result = fork1("sentinel", sentinel, NULL, USLOSS_MIN_STACK,
                   SENTINELPRIORITY);
   if (result < 0) {
      if (DEBUG && debugflag)
         console("startup(): fork1 of sentinel returned error, halting...\n");
      halt(1);
   }
  
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
int fork1(char *name, int (*f)(char *), char *arg, int stacksize, int priority) //TODO
{
   int proc_slot;

   if (DEBUG && debugflag)
      console("fork1(): creating process %s\n", name);

   /* test if in kernel mode; halt if in user mode */
    if ( (PSR_CURRENT_MODE & psr_get()) == 0 ) {
      //not in kernel mode
      console("fork1(): called while in user mode, by process %d. Halting...\n", Current->pid);
      halt(1);
    }

    disableInterrupts();

   /* Return if stack size is too small */
   if (stacksize <USLOSS_MIN_STACK){
      if (DEBUG && debugflag)
         console("Stack too small");

      return -2;
   }
   
   /* TODO find an empty slot in the process table */
   proc_slot = nextPid;

   // increment the next pid
   ++nextPid;

   /* fill-in entry in process table */
   if ( strlen(name) >= (MAXNAME - 1) ) {
      console("fork1(): Process name is too long.  Halting...\n");
      halt(1);
   }

   new_proc->status = STATUS_READY;
   new_proc->stacksize = stacksize;
   new_proc->stack = malloc(stacksize);
   new_proc->priority = priority;
   new_proc->start_func = f;
   new_proc->pid = new_pid;
   

   //strcpy(ProcTable[proc_slot].name, name);
   strcpy(new_proc->name, name);
   //ProcTable[proc_slot].start_func = f;

   if ( arg != NULL ){
      //ProcTable[proc_slot].start_arg[0] = '\0';

      if ( strlen(arg) >= (MAXARG - 1) ) {

         console("fork1(): argument too long.  Halting...\n");
         halt(1);
      }

      //strcpy(ProcTable[proc_slot].start_arg, arg);
      strcpy(new_proc->start_arg, arg);
   }
   else{
      new_proc->start_arg[0] = '\0';
   }

   if(Current != NULL){

      ListAddNode(&Current->children, new_proc);
      new_proc->parent_proc_ptr = Current;
   }

   numProc++;
   AddReadyProc(new_pid); // add to the list of ready procs

   // Initialize context for this process, but use launch function pointer for
   // the initial value of the process's program counter (PC)

   context_init(&(ProcTable[proc_slot].state), psr_get(),
                ProcTable[proc_slot].stack, 
                ProcTable[proc_slot].stacksize, launch);

   // for future phase(s)
   //p1_fork(ProcTable[proc_slot].pid);
   p1_fork(new_proc->pid);

   // set to false at the end of startup
   if(readyToStart){
      dispatcher();
   }

   enableInterrupts();


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

   if(Current->quittingChildren.count > 0){

      //pChild - ListPopNode(&Current->quittingChildren);
   }
   else{

      /*Block until a child quits */
      Current->status = STATUS_JOIN_BLOCKED; // we will be contexted out in the dispatcher

      dispatcher();

      //TODO disable ints

      //pChild = ListPopNode(&Current->quittingChildren);
   }
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
   if (Current->parent_proc_ptr !=NULL){
      // add process to quitters list
      ListRemoveNode(&Current->parent_proc_ptr->children, Current);     // take off of children list put on quitting list 
      ListAddNode(&Current->parent_proc_ptr->quittingChildren, Current); // TODO funcs. for List linked list

      // set to ready
      if (Current->parent_proc_ptr->status == STATUS_JOIN_BLOCKED){
         
         AddReadyProc(Current->parent_proc_ptr->pid);
      }
   }

   dispatcher();

   p1_quit(Current->pid);

   enableInterrupts();

} /* quit */

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
void dispatcher(void)
{
   proc_ptr next_process;
   context *pPrevContext = NULL;

   //TODO figure out: p1_switch
   p1_switch(Current->pid, next_process->pid);

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
//int sentinel (char * dummy)
int sentinel (void *)
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
