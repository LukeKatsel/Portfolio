#include "pch.h"


/*********************************************************************************
*
* SchedulerTest01
*
* Creates two child processes and waits for each to terminate.
*
* Expected Output:
*
*********************************************************************************/
int SchedulerTest01(char* arg)
{
    int status = -1, pid1, pid2, kidpid = -1;
    char* testName = __func__;

    printf("%s: started\n", testName);

    pid1 = k_spawn("P1-C1", SimpleWaitExit, "P1-C1", THREADS_MIN_STACK_SIZE, 3);
    printf("%s: after spawn of child with pid %d\n", testName, pid1);

    pid2 = k_spawn("P1-C2", SimpleWaitExit, "P1-C2", THREADS_MIN_STACK_SIZE, 3);
    printf("%s: after spawn of child with pid %d\n", testName, pid2);

    printf("%s: waiting on child process\n", testName);
    kidpid = k_wait(&status);
    printf("%s: exit status for child %d is %d\n", testName, kidpid, status);

    printf("%s: waiting on child process\n", testName);
    kidpid = k_wait(&status);

    printf("%s: exit status for child %d is %d\n", testName, kidpid, status);
    return 0;
}
