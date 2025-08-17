
#include "pch.h"
#include "THREADS.h"
#include "SchedulerTests.h"


// REMOVE

/*********************************************************************************
*
* SchedulerTest06
*
* spawns a simple child of a lower priority, then signals, joins, and waits. 
*
* Expected Output:
*
*********************************************************************************/
int SchedulerTest06(void* pArgs)
{
    int status = -1, pid1;
    int result;
    char* testName = __func__;
    int exitCode;

    /* spawn one simple child process at a lower priority. */
    printf("%s: started\n", testName);
    pid1 = k_spawn("P1-C1", WaitForSignal, "P1-C1", THREADS_MIN_STACK_SIZE, 1);

    k_signal(pid1, SIG_TERM);
    k_join(pid1, &exitCode);
    printf("%s: after joining child, status = %d\n", testName, exitCode);

    printf("%s: waiting on child process\n", testName);
    result = k_wait(&status);
    printf("%s: wait return code = %d\n", testName, result);

    k_exit(0);
    return 0;

}
