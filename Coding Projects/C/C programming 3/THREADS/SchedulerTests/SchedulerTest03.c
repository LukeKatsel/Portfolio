
#include "pch.h"
#include "THREADS.h"
#include "SchedulerTests.h"


int SimpleWaitExit(void* pArgs);
int JoinTwoLower(char* strArgs);


/*********************************************************************************
* 
* SchedulerTest03
*
* Tests basic join features.  
*
* Expected Output:
*
*********************************************************************************/
int SchedulerTest03(void* pArgs)
{
    int status = -1, pid1, kidpid = -1;
    char* testName = __func__;

    /* spawn one simple child process at a lower priority. */
    printf("%s: started\n", testName);
    pid1 = k_spawn("P1-C1", JoinTwoLower, "P1-C1", THREADS_MIN_STACK_SIZE, 3);
    printf("%s: after spawn of child with pid %d\n", testName, pid1);
 
    ps();

    /* Join with the child and print the results. */
    printf("%s: waiting on child process\n", testName);
    kidpid = k_wait(&status);
    printf("%s: exit status for child %d is %d\n", testName, kidpid, status);

    k_exit(0);

    return 0;
}

int JoinTwoLower(char* strArgs)
{
    int child1, child2;
    int status = 0xff;
    char nameBuffer[1024];
    int exitCode;

    if (strArgs != NULL)
    {
        printf("%s: started\n", strArgs);

        printf("%s: performing spawn of first child\n", strArgs);
        snprintf(nameBuffer, sizeof(nameBuffer), "%s-C1", strArgs);
        child1 = k_spawn(nameBuffer, SimpleWaitExit, nameBuffer, THREADS_MIN_STACK_SIZE, 1);
        printf("%s: spawn of first child returned pid = %d\n", strArgs, child1);

        printf("%s: performing spawn of second child\n", strArgs);
        snprintf(nameBuffer, sizeof(nameBuffer), "%s-C2", strArgs);
        child2 = k_spawn(nameBuffer, SimpleWaitExit, nameBuffer, THREADS_MIN_STACK_SIZE, 1);
        printf("%s: spawn of first child returned pid = %d\n", strArgs, child2);

        ps();

        printf("%s: joining with first child\n", strArgs);
        k_join(child1, &exitCode);
        printf("%s: after joining first child, status = %d\n", strArgs, exitCode);

        ps();

        printf("%s: joining with second child\n", strArgs);
        k_join(child2, &exitCode);
        printf("%s: after joining second child, status = %d\n", strArgs, exitCode);

        ps();

        printf("%s: performing waits\n", strArgs);
        child1 = k_wait(&status);
        printf("%s: first wait returned kid_pid = %d, status = %d\n", strArgs,
            child1, status);

        child2 = k_wait(&status);
        printf("%s: second wait returned kid_pid = %d, status = %d\n", strArgs,
            child2, status);
    }
    k_exit(-3);
    return 0;
}