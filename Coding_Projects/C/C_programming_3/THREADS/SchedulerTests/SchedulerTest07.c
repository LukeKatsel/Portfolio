
#include "pch.h"
#include "THREADS.h"
#include "SchedulerTests.h"

/*********************************************************************************
*
* SchedulerTest07
*
* Test
*
* Expected Output:
*
*********************************************************************************/
int SchedulerTest07(void* pArgs)
{
    int status = -1, pid1;
    int result;
    char* testName = __func__;

    /* spawn one simple child process at a lower priority. */
    printf("%s: started\n", testName);
    pid1 = k_spawn("P1-C1", SpawnOneHigher, "P1-C1", THREADS_MIN_STACK_SIZE, 3);

    printf("%s: wait on child process\n", testName);
    result = k_wait(&status);
    printf("%s: wait return code = %d\n", testName, result);

    k_exit(0);

    return 0;

} 