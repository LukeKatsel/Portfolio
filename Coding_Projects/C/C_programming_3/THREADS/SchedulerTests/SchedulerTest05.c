
#include "pch.h"
#include "THREADS.h"
#include <string.h>
#include "SchedulerTests.h"

/*********************************************************************************
*
* SchedulerTest05
*
* Test verifies the time slicing functions by spawning three children that have
* a delay.  The child with a 3 at the end of the name will dump the proc table
* part way through the delay.  The proc table should show non-zero values for
* CPU time for each of the children.
*
* Expected Output:
*
*********************************************************************************/
int SchedulerTest05(void* pArgs)
{
    int status = -1, kidpid = -1;
    int i, j;
    char nameBuffer[1028];
    char* testName = __func__;
    int count = 1;

    printf("%s: started\n", testName);
    for (j = 0; j < 2; j++)
    {
        for (i = 2; i < 6; i++)
        {
            snprintf(nameBuffer, sizeof(nameBuffer), "P1-C%d", count++);
            kidpid = k_spawn(nameBuffer, DelayAndDump, nameBuffer, THREADS_MIN_STACK_SIZE, 3);
            printf("%s: after spawn of child with pid %d\n", testName, kidpid);
        }

        for (i = 2; i < 6; i++)
        {
            kidpid = k_wait(&status);
            printf("%s: after wait on child %d, status = %d\n",
                testName, kidpid, status);
        }
    }
    k_exit(0);

    return 0;
}
