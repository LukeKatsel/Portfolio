#define DEBUG 1

typedef struct proc_struct proc_struct;

typedef struct proc_struct * proc_ptr;

typedef struct process_queue process_queue;

struct process_queue{
    proc_ptr head;
    proc_ptr tail;
    int      size;
    int  que_type;
};

struct proc_struct {
    proc_ptr       next_proc_ptr;
    proc_ptr       child_proc_ptr;
    proc_ptr       next_sibling_ptr;
    proc_ptr       parent_proc_ptr;
    proc_ptr       next_zapped_ptr;


   char           name[MAXNAME];     /* process's name */
   char           start_arg[MAXARG]; /* args passed to process */
   context        state;             /* current context for process */
   short          pid;               /* process id */
   short          proc_table_slot;   /* process table */
   short          ppid;              /* parent process id */
   int            priority;
   int (* start_func) (char *);      /* function where process begins -- launch */
   char          *stack;
   unsigned int   stacksize;
   int            status;            /* EMPTY, READY, RUNNING, ETC.. */
   /* other fields as needed... */

   int      child_quit_status;    // Status of child process when it quits
   short    child_quit_pid;       // PID of the child process when it quits
   int      child_has_quit;       // Flag indicating if child process has quit
   int      cpu_time;             // CPU time consumed by the process
   int      start_time;           // Time when the process started
   int      slice_time;           // Time slice allocated for the process

	process_queue   child_queue;           // Queue of the process's children
	int             quit_status;           // Status returned by the process when it quits
	process_queue   dead_child_queue;      // List of children who have quit in the order they have quit
	proc_ptr        next_dead_sibling_ptr; // Pointer to the next dead sibling process
	int             zap_status;            // Flag indicating whether the process has been zapped (1 if zapped, 0 if not)
	process_queue   zap_queue;             // Queue of processes waiting to be zapped by this process
	proc_ptr        next_zap_ptr;          // Pointer to the next process in the zap queue

	int     zapping_proc_ids[10];  // Array to store the IDs of processes being zapped
	int     zap_index;             // Index for the zapping_proc_ids array
};

struct psr_bits {
        unsigned int cur_mode:1;
       unsigned int cur_int_enable:1;
        unsigned int prev_mode:1;
        unsigned int prev_int_enable:1;
    unsigned int unused:28;
};

union psr_values {
   struct psr_bits bits;
   unsigned int integer_part;
};

/* Some useful constants.  Add more as needed... */
#define NO_CURRENT_PROCESS NULL
#define MINPRIORITY 5
#define MAXPRIORITY 1
#define SENTINELPID 1
#define SENTINELPRIORITY LOWEST_PRIORITY

/* Defining process statuses */
#define EMPTY 0
#define READY 1
#define RUNNING 2
#define JOIN_BLOCK 3
#define ZAP_BLOCK 4
#define QUIT 5
#define BLOCKED 6

//Queue types
#define READYLIST 1
#define CHILDQUE  2
#define ZAPPED    3
#define DEAD      4

//Quantum
#define TIMESLICE 80000