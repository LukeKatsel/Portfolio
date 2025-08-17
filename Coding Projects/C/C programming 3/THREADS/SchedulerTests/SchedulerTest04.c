
#include "pch.h"
#include "THREADS.h"
#include <string.h>
#include "SchedulerTests.h"

/*********************************************************************************
*
* SchedulerTest04
*
* spawns max number of processes, dumps the proc table, joins with all, then repeats
*
* Expected Output:
*
*********************************************************************************/
int SchedulerTest04(void* pArgs)
{
    int status = -1, kidpid = -1;
    int i, j;
    char nameBuffer[1028];
    char* testName = __func__;
    int count = 1;

    printf("%s: started\n", testName);
    for (j = 0; j < 2; j++)
    {
        for (i = 2; i < MAX_PROCESSES; i++)
        {
            snprintf(nameBuffer, sizeof(nameBuffer), "P1-C%d", count++);
            kidpid = k_spawn(nameBuffer, SimpleWaitExit, nameBuffer, THREADS_MIN_STACK_SIZE, 3);
            printf("start1(): after spawn of child %d\n", kidpid);
        }

        ps();

        for (i = 2; i < MAX_PROCESSES; i++)
        {
            kidpid = k_wait(&status);
            printf("%s: after wait on child %d, status = %d\n",
                testName, kidpid, status);
        }
    }

    k_exit(0);

    return 0;
}


