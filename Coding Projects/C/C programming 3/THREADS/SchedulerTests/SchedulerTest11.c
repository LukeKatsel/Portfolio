
#include "pch.h"
#include "THREADS.h"
#include "SchedulerTests.h"

/*********************************************************************************
*
* SchedulerTest11
* 
* Tests the spawn function kernel mode validation.
* 
* Expected Output:
* 
*********************************************************************************/
int SchedulerTest11(void *pArgs)
{
    int status = -1, pid1, kidpid = -1;
    char buffer[1028];
    char* testName = __func__;

    printf("%s: started\n", testName);
    snprintf(buffer, sizeof(buffer), "P1-C1 %d", getPid());

    /* set the mode to user mode. */
    SetPsr(GetPsr() & ~PSR_KERNEL_MODE);
    pid1 = k_spawn("P1-C1", SimpleWaitExit, "P1-C1", THREADS_MIN_STACK_SIZE, 3);
    printf("%s: after spawn of child with pid %d\n", testName, pid1);

    /* Join with the child and print the results. */
    printf("%s: waiting on child process\n", testName);
    kidpid = k_wait(&status);
    printf("%s: exit status for child %d is %d\n", testName, kidpid, status);
    k_exit(0);

    return 0; 
}
