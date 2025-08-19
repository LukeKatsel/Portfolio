/*  THREADS
*   Luke Katsel
*   5/5/2024
*
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "THREADS.h"
#include "Scheduler.h"
#include "Processes.h"

procStruct processTable[MAX_PROCESSES];
procStruct *runningProcess;
BOOL debugFlag = FALSE;
int nextPid = 1;
static int numProcsInTable = 0;
procQueue readyList[6];
procQueue blockList[6];

static int sentinel(char*);
void dispatcher();
static int launch(void *);
static void clockInterruptHandler(int dev, void* pUnit);
static void checkKernelMode(void);
static void disableInterrupts(void);
static void enableInterrupts(void);
static int getSlot(void);
static void addToQueue(procQueue *queue, procPtr process);
procPtr removeFromQueue(procQueue* queue, procPtr process);
static void initialization(int pid);
static void queueInit(procQueue* que, int type);
static void checkDeadlock(void);

int (*kinit) (void*);

IntHandler* intVector;



/*************************************************************************
   bootstrap()

   Purpose - This is the first function called by THREADS on startup.

             The function must setup the OS scheduler and primitive
             functionality and then spawn the first two processes.  
             
             The first two process are the sentinel process 
             and a startup process.  
             
             The startup process is used to initialize additional layers
             of the OS.  It is also used for testing the scheduler 
             functions.

   Parameters - void *pArgs - these arguments are unused at this time.

   Returns - The function does not return.

   Side Effects - The effects of this function is the launching of the kernel.

 *************************************************************************/
int bootstrap(void *pArgs){

    int result; /* value returned by call to spawn() */

    nextPid = 1;
    //runningProcess = NULL;

    /* initialize the process table */
    for (int i = 0; i < MAXPROC; i++) {

        // function to handle initialization
        initialization(i);
    }

    /* Initialize the Ready list, etc. */
    for (int i = 0; i < HIGHEST_PRIORITY + 1; i++) {
        readyList[i].head = NULL;
        readyList[i].tail = NULL;
        readyList[i].size = 0;
        readyList[i].que_type = READYLIST;
    }
    // set the running process to where sentinel will be
    runningProcess = &processTable[1];

    /* Initialize the clock interrupt handler */
    intVector = GetInterruptHandlers();
    intVector[THREADS_CLOCK_INTERRUPT] = clockInterruptHandler;

    /* TODO: startup a sentinel kernel thread for background processing. */
    result = k_spawn("sentinel", sentinel, NULL, 2 * THREADS_MIN_STACK_SIZE, LOWEST_PRIORITY);
    if (result < 0)
    {
        ConsoleOutput(debugFlag, "startup(): spawn for sentinel returned an error, Stopping...\n");
        Stop(1);
    }

    /* start the kinit thread.  Used as testing and for initializing the messaging layer.  */
    result = k_spawn("kinit", kinit, NULL, 2 * THREADS_MIN_STACK_SIZE, HIGHEST_PRIORITY);
    if (result < 0)
    {
        ConsoleOutput(debugFlag,"startup(): spawn for kinit returned an error, Stopping...\n");
        Stop( 1);
    }

    /* initialized and ready to go!! */

    /* this should never return since we are not a real process. */
    dispatcher();

    return 0;

}


/*************************************************************************
   spawn()

   Purpose - spawns a new process.
   
             Finds an empty entry in the process table and initializes
             information of the process.  Updates information in the
             parent process to reflect this child process creation.

   Parameters - the process procedure address, the size of the stack and
                the priority to be assigned to the child process.

   Returns - the process id of the created child or -1 if no child could
             be created or if priority is not between max and min priority.

   Side Effects - ReadyList is changed, procTable is changed, Current
                  process information changed
*************************************************************************/
int k_spawn(char* name, int (*f)(void *), void* arg, int stacksize, int priority){

    int procTableSlot;
    int new_pid = nextPid;
    procStruct *pNewProc;

    //debugging
    if (debugFlag) {
        ConsoleOutput(debugFlag, "spawn(): creating process %s\n", name);
    }

    /* Are we in kernel mode? */
    checkKernelMode();

    // disable interrupts???
    disableInterrupts();

    /* parameter validation */

    // name validation
    if (strlen(name) >= (MAXNAME - 1)){

        if (debugFlag) {
            ConsoleOutput(debugFlag, "spawn(): name too large.\n");
            return -2;
        }
    }
    // function validation
    if (f == NULL) {

        if (debugFlag) {
            ConsoleOutput(debugFlag, "spawn(): function is NULL.\n");
            return -1;
        }
    }
    // stacksize validation 
    if (stacksize < THREADS_MIN_STACK_SIZE) {

        if (debugFlag) {
            ConsoleOutput(debugFlag, "spawn(): stacksize too small.\n");
            return -2;
        }
    }
    // sentinel priority validation
    if (priority != LOWEST_PRIORITY && (strcmp(name, "sentinel") == 0)) {

        if (debugFlag) {
            ConsoleOutput(debugFlag, "spawn(): Sentinel needs sentinel priority\n");
            return -2;
        }
    }
    // priority validation
    if (priority > HIGHEST_PRIORITY || priority < LOWEST_PRIORITY) {

        if (debugFlag) {
            ConsoleOutput(debugFlag, "spawn(): Priority needs to be between 0 and 5\n");
            return -2;
        }
    }

        
    /* find an empty slot in the process table */

    // this loop will find the next available pid
    do {

        new_pid = nextPid++;
        // this function will check if the slot is occupied before assigning pid
    } while (getSlot(new_pid) == -1);

    /* mod the pid to get the entry in the process table */
    procTableSlot = new_pid % MAXPROC;

    // assign the new proc to the new slot
    pNewProc = &processTable[procTableSlot];


    /* initialize lists, status, etc */

    strcpy(pNewProc->name, name);   // name 
    if (arg != NULL){               // args
        
        // argument validation 
        if (strlen(arg) >= (THREADS_MAX_NAME - 1)){

            ConsoleOutput(debugFlag, "spawn(): argument too long.  Halting...\n");
            Stop( 1);
        }
        strcpy(pNewProc->start_arg, arg);
    }
    else{
 
        pNewProc->start_arg[0] = '\0';
    }
    /* Initialize context for this process, but use launch function pointer for
      the initial value of the process's program counter (PC) */
    pNewProc->context = ContextInitialize(launch, stacksize, arg); // context
    pNewProc->pid = new_pid;    //pid
    pNewProc->priority = priority;  //priority
    pNewProc->startFunction = f;    // start function
    pNewProc->stacksize = stacksize;    // stacksize
    pNewProc->slot = procTableSlot;
    pNewProc->cpuTime = 0;

    if (runningProcess->pid > -1){

        if (strcmp(runningProcess->name, "sentinel") != 0){

            // if not sentinel then put new proc in parent's list
            pNewProc->parent_proc_ptr = runningProcess;
            addToQueue(&runningProcess->childList, pNewProc);
        }
    }

    /* Add the process to the ready list */
    addToQueue(&readyList[priority], pNewProc);
    pNewProc->status = READY;   // status

    // if the new priority is higher then run it
    if (priority > runningProcess->priority) {
        dispatcher();
    }

    // enable interrupts
    enableInterrupts();

    return pNewProc->pid;
} /* spawn */

/*************************************************************************
   Name - launch
   Purpose - Dummy function to enable interrupts and launch a given process
             upon startup.
   Parameters - none
   Returns - nothing
   Side Effects - enable interrupts
*************************************************************************/
static int launch(void *args)
{
    int result;

    if (debugFlag) {
        ConsoleOutput(debugFlag, "launch(): started: %s\n", runningProcess->name);
    }

    /* Enable interrupts */
    enableInterrupts();

    /* Call the function passed to spawn, and capture its return value */
    runningProcess->status = RUNNING;
    result = runningProcess->startFunction(runningProcess->start_arg);

    if (debugFlag) {
        ConsoleOutput(debugFlag, "Process %d returned to launch\n", runningProcess->pid);
    }

    k_exit(result);

    return 0;
} /* launch */

/*************************************************************************
   Name - k_join
   Description       k_join function blocks the calling process's execution 
                    until the specified process, identified by pid, terminates. 
                    Unlike k_wait, which is tailored for child processes, 
                    k_join can be used to wait for any process, offering greater 
                    flexibility in process synchronization. Upon the target 
                    process's termination, k_join uses the pExitCode parameter 
                    to pass back the process's exit code, facilitating 
                    communication of the termination status.

    Arguments       pid- The Process ID of the target process the caller 
                    wishes to wait for. It is not restricted to child 
                    processes, allowing for broader synchronization use cases.

    pExitCode       A pointer to an integer where the exit code of the exiting 
                    process will be stored, providing insight into the 
                    termination reason or status.

    Return Value    int - Returns 0 on successful completion when the target 
                    process exits, and its exit code is successfully retrieved.
                    If an error occurs, the function returns one of the 
                    following values:
                    -2: Indicates an invalid pid was specified, such as one 
                    that does not exist or cannot be waited on by the caller.
                    -5: Indicates that the calling process was interrupted 
                    by a signal while waiting.
*************************************************************************/
int k_join(int pid, int* pChildExitCode){

    procPtr dyingProc;

    disableInterrupts();

    //debugging
    if (debugFlag) {
        ConsoleOutput(debugFlag, "Join()\n");
    }

    // check if pid is valid
    if (processTable[pid % MAXPROC].status == EMPTY) {
       
        ConsoleOutput(debugFlag, "Join(): pid is incorrect\n");
        return -2;
    }

    // proc cannot wait on parent
    if (&processTable[pid % MAXPROC] == runningProcess->parent_proc_ptr) {

        ConsoleOutput(debugFlag, "join: process attempted to join parent.\n");
        Stop(2);
    }
    // proc that will be waited on
    dyingProc = &processTable[pid % MAXPROC];

    // if it hasn't finished yet
    if (processTable[pid % MAXPROC].status != QUIT) {

        // then block and wait on it
        dyingProc->waitingOnPid = runningProcess->pid;
        block(JOIN_BLOCK);
    }
    int codeToBePassed = dyingProc->quitStatus;
    
    // pass exit code to calling function
    *pChildExitCode = codeToBePassed;

    numProcsInTable--;

    // check if proc was signaled
    if (signaled()) {
        return -5;
    }
    enableInterrupts();

    return 0;
}

/*************************************************************************
   Name - k_signal
   Description          The k_signal function sends a signal to a process 
                        identified by pid. This mechanism allows for inter-process 
                        communication and control, enabling processes to 
                        influence the behavior of others in a controlled manner. 
                        As of now, the only supported signal is SIG_TERM, 
                        used to request the termination of the specified process. 
                        The function is designed to be expanded in the future 
                        with additional signals for more nuanced inter-process 
                        interactions.

    Arguments           pid - The Process ID of the target process to which 
                        the signal will be sent. It must be a valid PID 
                        of an existing process within the system.

                        signal - The signal to be sent to the process. 
                        Currently, the only supported signal is SIG_TERM 
                        (terminate), but the design anticipates future 
                        expansion with additional signals.

    Return Value        int - Returns 0 on successful signal delivery to 
                        the target process.If an error occurs, the function 
                        returns one of the following values:
                        -2: The specified pid is not valid, indicating 
                        that no process with the given PID exists.
                        -6: The specified signal is not supported. 
                        Currently, this would apply to any signal other 
                        than SIG_TERM.
*************************************************************************/
int k_signal(int pid, int signal)
{
    // valid pid?
    int slot = pid % MAXPROC;

    if (processTable[slot].status == EMPTY) {
        // process does not exist 
        if (debugFlag) {
            ConsoleOutput(debugFlag, "k_signal(): pid is invalid\n");
        }
        return -2;
    }

    // valid signal?
    if (signal != SIG_TERM) {
        // signal is not valid 
        if (debugFlag) {
            ConsoleOutput(debugFlag, "k_signal(): signal is invalid\n");
        }
        return -6;
    }

    // flag that it has been signaled
    processTable[slot].signaled = TRUE;
    processTable[slot].signal = signal;
    
    return 0;
}
/*************************************************************************
   Name - k_wait
   Description          The k_wait function suspends execution of the calling 
                        process until one of its child processes exits. 
                        It is designed to wait for any child process to terminate, 
                        without specifying a particular one. Upon a child's exit, 
                        the function returns the PID of the child that exited 
                        and uses the pChildExitCode parameter to pass back the 
                        child's exit code.

    Arguments           pChildExitCode - An output parameter through which 
                        the exiting child process's exit code is returned 
                        to the calling process.

    Return Value        int - On successful completion, returns the Process 
                        ID (PID) of the child process that exited.  If an 
                        error occurs, the function returns one of the following
                        values:
                        -4: The parent process has no children to wait for.
                        -5: The parent process received a signal while waiting.
*************************************************************************/
int k_wait(int* code){
    
    procPtr dyingChild;

    // disable interrupts with built in check kernel mode
    disableInterrupts();

    //initialize child
    int deadChildPid = 0;

    //debugging
    if (debugFlag) {
        ConsoleOutput(debugFlag, "Wait()\n");
    }

    // check if has kids
    if (runningProcess->childList.size < 1 && runningProcess->deadChildList.size < 1) {

        if (debugFlag) {
            ConsoleOutput(debugFlag, "Wait(): proc has no children\n");
        }
        return -4;
    }

    //check if process has any "dead" children 
    if (runningProcess->deadChildList.size == 0) {

        if (debugFlag) {
            ConsoleOutput(debugFlag, "Wait(): proc is being blocked\n");
        }
        block(WAIT_BLOCK);
    }

        //remove the child from top of queue
    dyingChild = removeFromQueue(&runningProcess->deadChildList, runningProcess->deadChildList.head);

    // find child's slot in proc table
    deadChildPid = dyingChild->pid;
    int slot = deadChildPid % MAXPROC;

    // pass code to calling function
    int codeToBePassed = dyingChild->quitStatus;
    *code = codeToBePassed;

    // clear out table entry
    initialization(deadChildPid);
    
    // reinsert the quit status into empty table entry to retain the code for future
    processTable[slot].quitStatus = codeToBePassed;

    // decrement proc counter
    numProcsInTable--;

    // was the process signaled?
    if (signaled()) {
        deadChildPid = -5;
    }
    enableInterrupts();

    return deadChildPid;
} /* wait */


/*************************************************************************
   Name - signaled
   Description          Determines if the calling process has received a signal. 
                        This function checks the process's signal state and returns 
                        a non-zero value if a signal has been received, indicating 
                        that the process should take appropriate action in response, 
                        such as termination or handling the signal in a predefined manner.

    Arguments           NONE

    Return Value        int - Returns FALSE/0 if the calling process was 
                        signaled; otherwise, returns TRUE/1.
*************************************************************************/
int signaled(){

    // if it was signaled, then this entry would've been updated
    return runningProcess->signaled;
}

/*************************************************************************
   Name - k_exit
   Description          The k_exit function terminates the calling process, 
                        allowing it to exit gracefully while passing an exit 
                        code back to the operating system or parent process. 
                        This function is essential for signaling the completion 
                        of a process's execution and its outcome. The exit 
                        code is used to convey the status of the process's 
                        termination, whether successful, failed, or otherwise, 
                        to any interested  parties, such as a parent process
                        waiting on this process to finish.

    Arguments           exitCode - An integer value that the process returns 
                        upon exit. This code can be used to indicate the 
                        success or failure of the process's execution, 
                        with common conventions being 0 for success and 
                        non-zero values for various error or status conditions.

    Return Value        NONE - As a terminating function, k_exit does not 
                        return to the caller.
*************************************************************************/
void k_exit(int code){

    // disable interrupts with built in check kernel mode
    disableInterrupts();

    // debug
    if (debugFlag){
        ConsoleOutput(debugFlag, "Exit() called \n");
    }

    //change status 
    runningProcess->status = QUIT;
    runningProcess->quitStatus = code;

    //pull off ready list
    removeFromQueue(&readyList[(runningProcess->priority)], runningProcess);

    // check if the proc have any children left
    if (runningProcess->childList.head != NULL) {

        ConsoleOutput(0, "quit(): Process with active children attempting to quit\n");
        Stop(1);
    }

    //if there isn't a parent then delete the process from table
    if (runningProcess->parent_proc_ptr == NULL) {

        initialization(runningProcess->pid);
        numProcsInTable--;
    }
    else {

        // move to dead status queue 
        removeFromQueue(&runningProcess->parent_proc_ptr->childList, runningProcess);
        addToQueue(&runningProcess->parent_proc_ptr->deadChildList, runningProcess);
 
        // check if a process is waiting on current process from join
        if (runningProcess->waitingOnPid != 0) {

            procPtr procFromList = processTable + runningProcess->waitingOnPid % MAXPROC;

            removeFromQueue(&blockList[procFromList->priority], procFromList);
            addToQueue(&readyList[procFromList->priority], procFromList);
        }
        
        // check is parent is waiting on this proc from wait()
        if (runningProcess->parent_proc_ptr->status == WAIT_BLOCK) {

            runningProcess->parent_proc_ptr->status = READY;

            addToQueue(&readyList[runningProcess->parent_proc_ptr->priority], runningProcess->parent_proc_ptr);
            removeFromQueue(&blockList[runningProcess->parent_proc_ptr->priority], runningProcess->parent_proc_ptr);
        }
    }

    // if were in kinit then we can clear out the table
    if (strcmp(runningProcess->name, "kinit") == 0){  

        for (int i = 0; i < MAXPROC; i++) {

            initialization(i);
        }
        numProcsInTable = 0;
        // make sure no more procs left // redundant
        for (int j = 0; j < MAXPROC; j++) {

            if (processTable[j].pid != -1) {
                numProcsInTable++;
            }
        }
    }
    enableInterrupts();
    dispatcher();

} /* k_exit*/

/*************************************************************************
   Name - dispatcher
   Purpose - dispatches ready processes.  The process with the highest
             priority (the first on the ready list) is scheduled to
             run.  The old process is swapped out and the new process
             swapped in.
   Parameters - none
   Returns - nothing
   Side Effects - the context of the machine is changed
   ----------------------------------------------------------------------- */
void dispatcher(){

    LPVOID* pPrevContext = NULL;
    procStruct *lastProcess = NULL;
    procStruct *nextProcess = NULL;
    int timeSliced = 0;
    BOOL irqFlag;

    // disable interrupts with built in check kernel mode
    disableInterrupts();

    // get the current time for later
    int currentClock = SystemClock();

    /* check to see if we are in an interrupt. */
    irqFlag = GetPsr() & PSR_IRQ_MODE;

    // if the current process is running, then move it to ready
    if (runningProcess->status == RUNNING || runningProcess->sliceTime > TIMEALLOTMENT) {

        runningProcess->status = READY;
        removeFromQueue(&readyList[runningProcess->priority], runningProcess);
        addToQueue(&readyList[runningProcess->priority], runningProcess);
    }

    // get the next ready process
    for (int i = HIGHEST_PRIORITY; i > LOWEST_PRIORITY - 1; i--) {

        if (readyList[i].size > 0) {
            nextProcess = readyList[i].head;
            break;
        }
    }

    // no more procs in table
    if (nextProcess == NULL)
    {
        ConsoleOutput(debugFlag, "There are no ready procs.\n");
        Stop(1);
    }

    // make sure not a duplicate process
    if (nextProcess != runningProcess){

        // change the running process to new process
        lastProcess = runningProcess;

        /* Set the global running process */
        runningProcess = nextProcess;

        // reset slice and start time
        runningProcess->sliceTime = 0;
        runningProcess->startTime = currentClock;

        /* Set the status to running */
        runningProcess->status = RUNNING; 

        // if new process is sentinel
        if (strcmp(runningProcess->name, "sentinel") == 0){

            // clear out kinit from table
            if (lastProcess->pid != -1) {
                initialization(lastProcess->pid);
            }
            numProcsInTable--;
            
            checkDeadlock();
        }

        // if the last process was not sentinel
        if (strcmp(lastProcess->name, "sentinel") != 0){

            // capture the total cpu time
            lastProcess->cpuTime += (currentClock - lastProcess->startTime);
        }

        // enable interrupts and switch context
        enableInterrupts();
        
        if (irqFlag){

            ContextSwitch(CONTEXT_MODE_INTERRUPT, runningProcess->context);
            
        }
        else{

            ContextSwitch((lastProcess == NULL) ? CONTEXT_MODE_BOOTSTRAP : CONTEXT_MODE_NORMAL, runningProcess->context);
        }
    }
    else if (runningProcess != NULL && nextProcess != NULL){

        if (!irqFlag){

            /* Enable interrupts unless we are in an interrupt. */
            enableInterrupts();
        }
    }

} /* dispatcher */

/*************************************************************************
   Name - getPid
   Description          The getPid function is a kernel-level utility that 
                        returns the Process ID (PID) of the calling process. 
                        Within the kernel, this function is pivotal for the 
                        scheduler and other system components to uniquely 
                        identify and manage processes. Other kernel functions can 
                        use this value to find a process’s entry in the process table.

Arguments               NONE

Return Value            int - Returns the PID of the calling process, allowing 
                        kernel components to reference the process uniquely.
*************************************************************************/
int getPid(){

    // the calling process with have a pid entry
    return runningProcess->pid;
}


/*************************************************************************
   Name - ps
   Description          The ps function will print the contents of the proccess
                        table to the screen.

    Arguments           NONE

    Return Value        NONE - simply prints to the screen
*************************************************************************/
void ps(){

    // formatted header
    ConsoleOutput(0, "%-7s %-8s %-9s %-13s %-8s %-8s %-10s\n", "PID", "Parent", "Priority", "Status", "# Kids", "CPUtime", "Name     ");

    // loop through each entry
    for (int slot = 0; slot < MAXPROC; slot++) {
        if (processTable[slot].status != EMPTY) {

            // print out first 3 columns depending on if there's a parent or not
            if (processTable[slot].parent_proc_ptr == NULL) {

                ConsoleOutput(0, "%-7d %-8s %-9d ", processTable[slot].pid, "-1", processTable[slot].priority);
            }
            else {

                ConsoleOutput(0, "%-7d %-8d %-9d ", processTable[slot].pid, processTable[slot].parent_proc_ptr->pid, processTable[slot].priority);
            }
            // switch case to print status string
            switch (processTable[slot].status) {

                case EMPTY:
                    ConsoleOutput(0, "% -13s", "EMPTY");
                    break;
                case READY:
                    ConsoleOutput(0, "% -13s", "READY");
                    break;
                case RUNNING:
                    ConsoleOutput(0, "% -13s", "RUNNING");
                    break; 
                case WAIT_BLOCK:
                    ConsoleOutput(0, "% -13s", "WAIT BLOCK");
                    break;
                case QUIT:
                    ConsoleOutput(0, "% -13s", "QUIT");
                    break;
                case JOIN_BLOCK:
                    ConsoleOutput(0, "% -13s", "JOIN BLOCK");
                    break;
                default:
                    ConsoleOutput(0, "ERROR");
            }
            // print out last 3 columns 
            ConsoleOutput(0, " %-8d %-8d %-8s\n", processTable[slot].childList.size, processTable[slot].cpuTime, processTable[slot].name);
        }
    }
}

/*************************************************************************
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
static int sentinel(char* dummy){

    // infinite loop, just need to check for deadlock 
    while (1){

        checkDeadlock();

    }
    return 0;
} /* sentinel */


/*************************************************************************
   Name - readTime
   Description          Returns the amount of CPU time in milliseconds that 
                        the current process has used. This function is essential 
                        for monitoring process performance, optimizing resource 
                        allocation, and implementing functionality that relies on 
                        understanding a process's consumption of CPU resources.

    Arguments           NONE

    Return Value        int - The CPU time used by the calling process, measured
                        in milliseconds.
*************************************************************************/
int readTime(void){

    int time = -1;

    return time;

} /* readTime */

/*************************************************************************
   Name - block
   Description          Adjusts the calling process's execution status to 
                        "blocked" based on the specified block_status. 
                        This function is used to temporarily suspend a 
                        process's execution, preventing it from using CPU 
                        resources until certain conditions are met, at which 
                        point it can be unblocked using the unblock function.

    Arguments           block_status - An integer value specifies the new status 
                        to associate with a process. The value of block_status must 
                        be > 10. If the value is not > 10, then the function 
                        must print and error message and halt the kernel with 
                        a Stop(1) call.

    Return Value        int - Returns 0 on successfully blocking the process. 
                        The function should return -5 if the process was 
                        signaled while blocked.
*************************************************************************/
int block(int newStatus)
{
    disableInterrupts();

    runningProcess->status = newStatus;

    // remove proc from ready list and add to block list
    removeFromQueue(&readyList[runningProcess->priority], runningProcess);
    addToQueue(&blockList[runningProcess->priority], runningProcess);

    dispatcher();
    
    // was the proc signaled?
    if (signaled()) {

        return -1;
    }
    return 0;
} 

/*************************************************************************
   Name - unblock
   Description          Restores a previously blocked process, identified 
                        by pid, to a state where it can be considered for 
                        execution by the scheduler. This function is essential 
                        for resuming processes that were suspended due to 
                        waiting on resources, synchronization conditions, 
                        or other temporary states that no longer apply.

    Arguments           pid - An integer value specifies the new status 
                        to associate with a process.

    Return Value        int - Returns 0 on successfully unblocking the specified process.
                        If an error occurs, the function returns one of the following values:
                        -2: The specified pid is not valid, if the specified 
                        process is not blocked, or if the process is blocked 
                        in join or wait (e.g. the status is < 10).
*************************************************************************/
int unblock(int pid){

    // disable interrupts with built in check kernel mode
    disableInterrupts();

    //check pid
    if (processTable[pid % MAXPROC].status != JOIN_BLOCK && processTable[pid % MAXPROC].status != WAIT_BLOCK) {

        // process is not blocked;
        enableInterrupts();
        return -1;
    }

    procPtr procToBeUnblocked = processTable + (pid % MAXPROC);

    procToBeUnblocked->status = READY;

    // remove from block list and add to ready list
    addToQueue(&readyList[procToBeUnblocked->priority], procToBeUnblocked);
    removeFromQueue(&blockList[procToBeUnblocked->priority], procToBeUnblocked);

    dispatcher();

    // proc has been signaled;
    if (signaled()) {

        enableInterrupts();
        return -1;
    }

    enableInterrupts();
    return 0;
} 

/*************************************************************************
   Name - getStartTime
   Description              Retrieves the start time of the calling process, 
                            represented as a value from the system clock. 
                            This function is essential for monitoring process 
                            duration, resource usage timing, and scheduling 
                            decisions based on process age or execution time.

    Arguments               NONE

    Return Value            int - Returns the start time of the calling process 
                            as an integer value from the system clock.
*************************************************************************/
int getStartTime(void) {

    // return the start time of running function
    return runningProcess->startTime;
} /* getStartTime */

/*************************************************************************
   Name - readClock
   Description              readClock retrieves the current value of the system 
                            clock, measured in milliseconds. This function 
                            is essential for timekeeping within the operating 
                            system, allowing processes and the scheduler to 
                            obtain precise timing information for a variety 
                            of purposes, including performance monitoring, 
                            timeout management, and time-based scheduling decisions.

    Arguments               NONE

    Return Value            DWORD - Returns the current value of the system 
                            clock as a DWORD, representing time in milliseconds.
*************************************************************************/
DWORD readClock(){

    // get the current time
    return SystemClock();
} /* readClock */

/*************************************************************************
   Name - timeSlice
   Description          Invokes a scheduling event to potentially switch 
                        the currently running process based on the system's 
                        scheduling policy. timeSlice is typically called by 
                        the system clock interrupt handler ensure fair CPU 
                        allocation among all ready processes, adhering to 
                        the scheduler's time-sharing strategy.

    Arguments           NONE

    Return Value        NONE
*************************************************************************/
void timeSlice(void) {

    disableInterrupts();

    // record the slice time
    runningProcess->sliceTime = SystemClock() - runningProcess->startTime;
    
    // if the slice is more than allowed time
    if (runningProcess->sliceTime > TIMEALLOTMENT) {

        // reset time slice and call dispatcher
        runningProcess->sliceTime = 0;
        dispatcher();
    }
    else {
        enableInterrupts();
    }
}


/*************************************************************************
   Name - clockInterruptHandler
   This function will call timeSlice() when a clock interrupt occurs
*************************************************************************/
static void clockInterruptHandler(int dev, void* pUnit){

    // call time slick during clock interrupt
    timeSlice();
}


/*************************************************************************
   Name - checkKernelMode
   This function will make sure that execution is occurring in Kernel mode.
   If not in Kernel Mode then Stop() will be called.
*************************************************************************/
static void checkKernelMode(void){

    // check the current mode
    if ((PSR_KERNEL_MODE & GetPsr()) == 0) {
        
        // if in user mode clear out proc table
        if (numProcsInTable > 0) {

            for (int i = 1; i < MAXPROC; i++) {
                initialization(i);;
            }
            numProcsInTable = 0;
         }
        // stop program
         ConsoleOutput(TRUE, "Kernel mode expected, but function called in user mode.\n");
         Stop(1);
    }
}


/*************************************************************************
   Name - disableInterrupts
   This functions disable interrupts
*************************************************************************/
static void disableInterrupts(void) {

    checkKernelMode();
    // make sure we are in kernel mode
    SetPsr(GetPsr() & ~PSR_IRQ_MODE);
    //disable interrupts
}


/*************************************************************************
   Name - enableInterrupts
   This functions enables interrupts
*************************************************************************/
static void enableInterrupts(void) {

    checkKernelMode();
    // make sure we are in kernel mode
    SetPsr(GetPsr() | PSR_IRQ_MODE);
    //enable interrupts
}


/*************************************************************************
   Name - getSlot
   This function will find an open slot in the processTable based on the 
   provided pid. 
*************************************************************************/
static int getSlot(int pid) {

    int slot = pid % MAXPROC;
    // find an open slot using the pid
    if (processTable[slot].status == EMPTY) {
        // found open slot so return location in proc table array
        numProcsInTable++;
        return slot;
    }
    return -1;
}


/*************************************************************************
   Name - addToQueue
   This function will add the given process to the given queue.
*************************************************************************/
static void addToQueue(procQueue *queue, procPtr process){

    // if there's nothing in queue then head and tail are new proc
    if (queue->head == NULL && queue->tail == NULL){

        queue->head = queue->tail = process;
    }
    else{
        // add the proc to the tail of the selected list
        if (queue->que_type == READYLIST) {
            queue->tail->next_ready_proc_ptr = process;// here
        }
        else if (queue->que_type == CHILDQUE) {
            queue->tail->next_child_ptr = process;
        }
        else if (queue->que_type == SIGNALEDQUE) {
            queue->tail->next_signaled_ptr = process;
        }
        else if (queue->que_type == DEAD) {
            queue->tail->next_dead_child_ptr = process;
        }
        queue->tail = process;
    }
    // increment the list size
    queue->size++;
}

/*************************************************************************
   Name - removeFromQueue
   This function will remove the given process from the given queue.
*************************************************************************/
procPtr removeFromQueue(procQueue* queue, procPtr process){

    procPtr temp = queue->head;
    procPtr temp2;
    // check if there's anything in list
    if (queue->head == NULL){

        return NULL;
    }
    // check if there's more than one proc
    if (queue->head == queue->tail){

        queue->head = queue->tail = NULL;
    }
    else{

        // pull off head node and shift other nodes 
        if (queue->que_type == READYLIST){

            temp2 = temp->next_ready_proc_ptr;
            //if process to be removed is first in queue
            //remove process and set head = to second in line.
            if (temp == process){

                queue->head = temp2;
                queue->size--;
                return temp;
            }
            // keep looking for process
            while (temp2 != process){

                temp = temp->next_ready_proc_ptr;
                temp2 = temp2->next_ready_proc_ptr;
            }
            if (temp2 == process){

                if (temp2->next_ready_proc_ptr != NULL){

                    temp->next_ready_proc_ptr = temp2->next_ready_proc_ptr;
                    queue->size--;
                    return temp2;
                }
            }
            temp->next_ready_proc_ptr = NULL;
            // decrement size and return the desired proc
            queue->size--;
            return temp2;
        }
        else if (queue->que_type == CHILDQUE){

            temp2 = temp->next_child_ptr;

            if (temp == process){

                queue->head = temp2;
                queue->size--;
                return temp;
            }
            while (temp2 != process){

                temp = temp->next_child_ptr;
                temp2 = temp2->next_child_ptr;
            }
            if (temp2 == process){

                if (temp2->next_child_ptr != NULL){

                    temp->next_child_ptr = temp2->next_child_ptr;
                    queue->size--;
                    return temp2;
                }
            }
            temp->next_child_ptr = NULL;
            queue->size--;
            return temp2;
        }
        else if (queue->que_type == DEAD){

            temp2 = temp->next_dead_child_ptr;

            if (temp == process){

                queue->head = temp2;
                queue->size--;
                return temp;
            }
            while (temp2 != process){

                temp = temp->next_dead_child_ptr;
                temp2 = temp2->next_dead_child_ptr;
            }
            if (temp2 == process){

                if (temp2->next_dead_child_ptr != NULL){

                    temp->next_dead_child_ptr = temp2->next_dead_child_ptr;
                    queue->size--;
                    return temp2;
                }
            }
            temp->next_dead_child_ptr = NULL;
            queue->size--;
            return temp2;
        }
    }
    // decrement size and return the desired proc
    queue->size--;
    return temp;

}


/*************************************************************************
   Name - initialization
   This function will clear out a slot in the processTable based on the 
   given pid.
*************************************************************************/
static void initialization(int pid){

    // initialize process with pid
    int slot = pid % MAXPROC;

    queueInit(&processTable[slot].childList, CHILDQUE);
    queueInit(&processTable[slot].deadChildList, DEAD);

    processTable[slot].next_ready_proc_ptr = NULL;
    processTable[slot].next_child_ptr = NULL;
    processTable[slot].next_signaled_ptr = NULL;
    processTable[slot].next_dead_child_ptr = NULL;
    processTable[slot].parent_proc_ptr = NULL;

    processTable[slot].name[0] = '\0';
    processTable[slot].start_arg[0] = '\0';
    processTable[slot].pid = -1;
    processTable[slot].slot = -1;
    processTable[slot].quitStatus = -1;
    processTable[slot].priority = -1;
    processTable[slot].startFunction = NULL;
    processTable[slot].stacksize = 0; 
    processTable[slot].status = EMPTY;

    

    processTable[slot].signaled = FALSE;
    processTable[slot].signal = 0;
    processTable[slot].startTime = 0;
    processTable[slot].sliceTime = 0;
    processTable[slot].cpuTime = 0;
    processTable[slot].waitingOnPid = 0;
    processTable[slot].deadChildCode = 0;

}


/*************************************************************************
   Name - queueInit
   This function will clear out the provided queue.
*************************************************************************/
static void queueInit(procQueue* que, int type){

    // initialize a queue
    que->head = NULL;
    que->tail = NULL;
    que->size = 0;
    que->que_type = type;

}

/*************************************************************************
   Name - checkDeadlock
   This function will check if there are any processes in the processTable.
   If there are any processes then Stop() will be called.
*************************************************************************/
static void checkDeadlock(void){

    // disable interrupts with built in check kernel mode
    disableInterrupts();
   
    // if more than sentinel is left then stop program
    if (numProcsInTable > 1) {

        ConsoleOutput(TRUE, "checkDeadlock(): process is still present. Halting... \n");
        Stop(1);

    }
    else {
        ConsoleOutput(TRUE, "All processes completed.\n");
        Stop(0);
    }
    enableInterrupts();
}