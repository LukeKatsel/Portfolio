#pragma once

typedef struct procStruct procStruct;

typedef struct procStruct* procPtr;

typedef struct procQueue procQueue;

// status types
#define EMPTY 0
#define READY 1
#define RUNNING 2
#define WAIT_BLOCK 3 
#define QUIT 4
#define JOIN_BLOCK 5

//Queue types
#define READYLIST 1
#define CHILDQUE  2
#define	SIGNALEDQUE 3
#define	DEAD 4

#define TIMEALLOTMENT 600

struct procQueue {
	procPtr			head;
	procPtr			tail;
	int				size;
	int				que_type;
};

struct procStruct{

	/* Pointers for linked lists. */
	char			name[MAXNAME];		/* process's name */
	short			pid;

	procPtr			next_ready_proc_ptr;
	procPtr			next_child_ptr;
	procPtr			next_signaled_ptr;
	procPtr			next_dead_child_ptr;
	procPtr			parent_proc_ptr;

	procQueue		childList;
	procQueue		deadChildList;
	int				deadChildCode;

	char			start_arg[MAXARG];	/* args passed to process */
	void*			context;			/* current context for process */
	int				slot;
	int				quitStatus;
	int				priority;
	int (*startFunction) (void*);		/* function where process begins -- launch */
	unsigned int	stacksize;
	int				status;				/* READY, BLOCKED, QUIT, etc. */

	BOOL			signaled;
	int				signal;

	int				startTime;
	int				sliceTime;
	int				cpuTime;
	int				waitingOnPid;
};
