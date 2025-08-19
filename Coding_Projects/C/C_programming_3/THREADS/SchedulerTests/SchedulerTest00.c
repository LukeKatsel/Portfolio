#include "pch.h"

/*********************************************************************************
*
* SchedulerTest00
* 
* Simple test case that creates one child process and waits for it to terminate.
* 
* Expected Output:
* 
*********************************************************************************/
int SchedulerTest00(void *pArgs)
{
    int status=-1, pid1, kidpid=-1;
    char* testName = __func__;

    /* spawn one simple child process at a lower priority. */
    printf("%s: started\n", testName);
    pid1 = k_spawn("P1-C1", SimpleWaitExit, "P1-C1", THREADS_MIN_STACK_SIZE, 3);
    printf("%s: after spawn of child with pid %d\n", testName, pid1);

    /* Join with the child and print the results. */
    printf("%s: wait on child process\n", testName);
    kidpid = k_wait(&status);
    printf("%s: exit status for child %d is %d\n", testName, kidpid, status);

    k_exit(0);

    return 0;
}

