#pragma once 

#define STATUS_EMPTY 0
#define STATUS_USED 1
#define STATUS_ENDED 3


typedef struct userProcStruct* userProcPtr;

struct userProcStruct{
    userProcPtr parentPtr;
	userProcPtr nextPtr;
	userProcPtr Child;
	userProcPtr nextChild;
	int pid;
	int status;
	int numChildren;
	int mbox;
	int buffer;
	int mutex_mbox;
	int (*start_func)(void*);
	void* start_arg;
}; 


typedef struct SemaphoreStructure{
	int num;
	int status;
	int count;
	int mutex_mbox;
	userProcPtr block_list;
} Semaphore;