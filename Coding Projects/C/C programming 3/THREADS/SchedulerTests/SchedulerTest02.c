
#include "pch.h"
#include "THREADS.h"
#include "SchedulerTests.h"


/*********************************************************************************
*
* SchedulerTest02
*
* Spawns one child process at priority 3.  The child process spawns two
* children at a higher priority (4).  Those children should preempt its parent
* at spawn().
*
* Expected Output:
*
*********************************************************************************/
int SchedulerTest02(char* arg)
{
    int status = -1, pid1, kidpid = -1;
    char* testName = __func__;

    /* spawn one simple child process at a lower priority. */
    printf("%s: started\n", testName);
    pid1 = k_spawn("P1-C1", spawnTwoHigher, "P1-C1", THREADS_MIN_STACK_SIZE, 3);
    printf("%s: after spawn of child with pid %d\n", testName, pid1);

    /* Join with the child and print the results. */
    printf("%s: waiting on child process\n", testName);
    kidpid = k_wait(&status);
    printf("%s: exit status for child %d is %d\n", testName, kidpid, status);

    k_exit(0);

    return 0;
}

