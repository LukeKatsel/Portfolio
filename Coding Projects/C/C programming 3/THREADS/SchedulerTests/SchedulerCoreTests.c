
#include "pch.h"

#pragma optimize("",off)
int RandomDelayAndQuit(char* arg)
{
    unsigned long startTime, currentTime;
    int printingThread = 0;
    unsigned long stopAt;
    static int randSeed = 2200;

    srand(randSeed);

    randSeed = stopAt = rand() % 10000;
    char* testName = __func__;

    printf("%s: started\n", arg);

    startTime = readClock();
    while (1)
    {
        currentTime = readClock();

        if ((currentTime - startTime) > stopAt)
        {
            break;
        }

    }
    printf("%s: exitting, pid = %d\n", arg, getPid());
    k_exit(-getPid());
    return 0;
}

/*********************************************************************************
*
* SchedulerManyDifferentThreads
*
* Simple test case that creates one child process.
*
* Expected Output:
*
*********************************************************************************/
int SchedulerCoreTest1(void* pArgs)
{
    int status = -1, kidpid = -1;
    int i, j;
    char nameBuffer[1028];
    char* testName = __func__;
    int count = 1;

    printf("%s: started\n", testName);
    for (j = 0; j < 100; j++)
    {
        for (i = 2; i < 40; i++)
        {
            snprintf(nameBuffer, sizeof(nameBuffer), "P1-C%d", count++);
            kidpid = k_spawn(nameBuffer, RandomDelayAndQuit, nameBuffer, THREADS_MIN_STACK_SIZE, 3);
            printf("%s: after spawn of child with pid %d\n", testName, kidpid);
        }

        for (i = 2; i < 40; i++)
        {
            kidpid = k_wait(&status);
            printf("%s: after join of child %d, status = %d\n",
                testName, kidpid, status);
        }
    }
    k_exit(0);
    return 0;
}

