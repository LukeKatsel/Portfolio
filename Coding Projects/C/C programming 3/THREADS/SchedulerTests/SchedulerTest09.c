
#include "pch.h"
#include "THREADS.h"
#include "SchedulerTests.h"

/*********************************************************************************
*
* SchedulerTest09
* 
* spawn a child and quit without waiting.
* 
* Expected Output:
* 
*********************************************************************************/
int SchedulerTest09(void *pArgs)
{
    int status = -1, pid1, kidpid = -1;
    char* testName = __func__;

    /* spawn one simple child process at a lower priority. */
    printf("%s: started\n", testName);
    pid1 = k_spawn("P1-C1", SimpleWaitExit, "P1-C1", THREADS_MIN_STACK_SIZE, 3);
    printf("%s: after spawn of child with pid %d\n", testName, pid1);

    k_exit(0);

    return 0;
}
