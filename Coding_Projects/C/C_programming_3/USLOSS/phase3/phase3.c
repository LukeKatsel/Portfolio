#include <usloss.h>
#include <phase1.h>
#include <phase2.h>
#include <phase3.h>
#include <stdio.h>
#include <libuser.h>
#include <usyscall.h>
#include <sems.h>


struct userProcStruct UserProcTable[MAXPROC];


extern void (*sys_vec[MAXSYSCALLS])(sysargs *args);


extern int start3(void*);

//Semaphore MBoxTable[MAXSEMS]; TODO remove if not needed
int globalNumSems;
int globalSemBox;
int globalProcBox;


int start2(char *); 
int  spawn_real(char *name, int (*func)(char *), char *arg, int stack_size, int priority);
static int spawn_launch(char* ch);
int  wait_real(int *status);
void terminate_real(int exit_code);
void checkMode(void);
void sysNull(sysargs* sa);
static void spawn(sysargs* sa);
static void wait(sysargs* sa);
static void terminate(sysargs* sa);
static int tableAdd(int pid);
static int procSearch(int pid);
static void userMode(void);


int start2(char *arg)
{
    int		status;
    /*
     * Check kernel mode here.
     */
    checkMode();
    
    /*
     * Data structure initialization as needed...
     */
    int i;

    for (i = 0; i < MAXPROC; i++){

		UserProcTable[i].pid = -1;
	    UserProcTable[i].status = STATUS_EMPTY;
	    UserProcTable[i].mbox = MboxCreate(0, 0);
	    UserProcTable[i].mutex_mbox = MboxCreate(1, 0);
        UserProcTable[i].parentPtr = NULL;
        UserProcTable[i].nextPtr = NULL;
        UserProcTable[i].Child = NULL;
        UserProcTable[i].nextChild = NULL;
        UserProcTable[i].numChildren = 0;
        UserProcTable[i].buffer = 0;
	}

    for (i=0; i < MAXSYSCALLS; i++){
		sys_vec[i] = sysNull;
	}

    sys_vec[SYS_SPAWN] = spawn;
	sys_vec[SYS_WAIT] = wait;
	sys_vec[SYS_TERMINATE] = terminate;
	
	/* TODO remove if not needed 
	for (i = 0; i < MAXSEMS; i++){
		init_sem(i);
        int num;
	    int status;
	    int count;
	    int mutex_mbox;
	    userProcPtr block_list;
	}
    */

	globalProcBox = MboxCreate(1, 0);
	globalSemBox =MboxCreate(1,0);



    /*
     * Create first user-level process and wait for it to finish.
     * These are lower-case because they are not system calls;
     * system calls cannot be invoked from kernel mode.
     * Assumes kernel-mode versions of the system calls
     * with lower-case names.  I.e., Spawn is the user-mode function
     * called by the test cases; spawn is the kernel-mode function that
     * is called by the syscall_handler; spawn_real is the function that
     * contains the implementation and is called by spawn.
     *
     * Spawn() is in libuser.c.  It invokes usyscall()
     * The system call handler calls a function named spawn() -- note lower
     * case -- that extracts the arguments from the sysargs pointer, and
     * checks them for possible errors.  This function then calls spawn_real().
     *
     * Here, we only call spawn_real(), since we are already in kernel mode.
     *
     * spawn_real() will create the process by using a call to fork1 to
     * create a process executing the code in spawn_launch().  spawn_real()
     * and spawn_launch() then coordinate the completion of the phase 3
     * process table entries needed for the new process.  spawn_real() will
     * return to the original caller of Spawn, while spawn_launch() will
     * begin executing the function passed to Spawn. spawn_launch() will
     * need to switch to user-mode before allowing user code to execute.
     * spawn_real() will return to spawn(), which will put the return
     * values back into the sysargs pointer, switch to user-mode, and 
     * return to the user code that called Spawn.
     */

    tableAdd(getpid());

    int pid = spawn_real("start3", start3, NULL, 4*USLOSS_MIN_STACK, 3);
    pid = wait_real(&status);

	return 0;

} /* start2 */

int  spawn_real(char *name, int (*func)(char *), char *arg, int stack_size, int priority){

	userProcPtr temp;

	//fork a process
	int newPid = fork1(name, spawn_launch, NULL, stack_size, priority);
	
    // check for errors with fork 
	if (newPid >= 0) { 

        // look for pic in proc table
		int slot = procSearch(newPid);
        int kid= 0;

		if (slot < 0){
            //if not in table 
			slot = tableAdd(newPid);
            // add to table
        }

		else{
            // if already in table
		    kid = 1;
            // make sure that we utilize mboxsend
        }
		// search for slot in case we updated it with tableAdd
		slot = procSearch(newPid);

		if (slot < 0){
			console("spawn_real() pid %d not found", newPid);
			terminate_real(-1); 
		}

		UserProcTable[slot].start_func = func;
		UserProcTable[slot].start_arg = arg;

	
		int currSlot = procSearch(getpid());
        
		temp = &UserProcTable[currSlot];

		enqueue_child(&temp,&UserProcTable[slot]); //TODO remove if not needed

        UserProcTable[currSlot].Child = UserProcTable[slot];



		if (kid){
            // mutex operation
			MboxSend(UserProcTable[slot].mbox, NULL, 0);
        }

	}

    // return new process pid
	return newPid;
}

static int spawn_launch(char* ch){

    return 0;
}

int wait_real(int *status){

    int pid = join(status);

    return pid;
}

void terminate_real(int exit_code){

    int child_pid;
	int parent_slot;
	int child_slot;

	parent_slot = procSearch(getpid());
	//
	// Find everyone in the parent's child list that hasn't
	// terminated and zap them so we can terminate them in
	// spawn launch before they run
	//
	while (1) {
		//child_pid = remove_child(&UserProcTable[parent_slot]); // TODO remove if needed
		if (child_pid == -1)
			break;

		child_slot = procSearch(child_pid);

		if (UserProcTable[child_slot].status != STATUS_ENDED){
			zap(child_pid);
		}
	}

	//
	// now quit
	//
	UserProcTable[parent_slot].status =STATUS_ENDED;
	quit(exit_code);
}


void checkMode(void){

    if(! PSR_CURRENT_MODE & psr_get()){
		console("Not in kernel mode.\n");
		halt(1);
	}
}

void sysNull(sysargs* sa){
	terminate_real(-1);
}

static void spawn(sysargs* sa){ // TODO need to change up 

    int kid_pid;

	char* name;
	int (*func)(void*);
	void* arg;
	int stack_size;
	int priority;

	//
	// extract params from sysargs
	//
	func = sa->arg1;
	arg = sa->arg2;
	stack_size = (int)sa->arg3;
	priority = (int)sa->arg4;
	name = (char*)sa->arg5;

	//
	// validate parameters
	//
	if ((func==NULL)
	|| (stack_size < USLOSS_MIN_STACK)
	|| (priority < HIGHEST_PRIORITY || priority > LOWEST_PRIORITY)
	|| (name==NULL)){

		sa->arg1 = (void*)-1;
		sa->arg4 = (void*)-1;
	} else {
		//
		// perform actual spawning of the process
		//
		kid_pid = spawn_real(name, func, arg, stack_size, priority);
		if (kid_pid < 0){
			kid_pid = -1;
		}

		//
		// put returns values into sysargs
		//
		sa->arg1 = (void*)kid_pid;
		sa->arg4 = 0;
	}

	//
	// switch to user mode
	//
	userMode();

}

static void wait(sysargs* sa){

	int status;

	int pid = wait_real(&status);

	sa->arg1=(void*)pid;
	sa->arg2=(void*)status;
	if (pid == -2){
		sa->arg4=(void*)-1;
	} 
    else {
		sa->arg4=0;
	}

	userMode();

}
static void terminate(sysargs* sa){

	int status = (int)sa->arg1;

	terminate_real(status);

	userMode();
}


static int tableAdd(int pid){

    int slot = 0;

    // mutex operation
	MboxSend(globalProcBox, NULL, 0);

    // loop to find open proc slot
    while(slot < MAXPROC){

        if (UserProcTable[slot].status == STATUS_EMPTY){
			break;
		}
		slot++;
    }

    // if slot equals max num of procs 
	if (slot == MAXPROC){
		// then every proc slot id used
		return -1;
	}

    // if found slot then update pid
	UserProcTable[slot].pid = pid;
    // update status
	UserProcTable[slot].status = STATUS_USED;

    // mutex operation 
	MboxReceive(globalProcBox, NULL, 0);

	return slot;

}
static int procSearch(int pid){

    int slot = 0;
    //loop through proc table
    while(slot < MAXPROC){

        // search for pid in pid element
        if (UserProcTable[slot].pid == pid){
			break;
		} // return slot if found
		slot++;
    }
    // return -1 if looped through whole table with no luck 
	if (slot == MAXPROC){
		return -1;
	}

    return slot;
}
static void userMode(void){
	if (PSR_CURRENT_MODE & psr_get()){
		int set = 0xE; // 1110
		psr_set(psr_get() & set);
	} 
    else {
		console("already in user mode.\n");
	}
}