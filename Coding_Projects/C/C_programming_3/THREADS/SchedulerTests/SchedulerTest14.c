
#include "pch.h"
#include "THREADS.h"
#include "SchedulerTests.h"


int SpawnDumpProcess2(char* strArgs);
int SignalJoinGlobalPid(char* arg);

extern int gPid;

/*********************************************************************************
*
* SchedulerTest14
*
* Expected Output:
*
*********************************************************************************/
int SchedulerTest14(void* pArgs)
{
    int status = -1, pid2, kidpid = -1;
    char* testName = __func__;

    printf("%s: started\n", testName);

    gPid = k_spawn("P1-C1", SpawnDumpProcess2, "P1-C1", THREADS_MIN_STACK_SIZE, 4);
    printf("%s: after spawn of child with pid %d\n", testName, gPid);

    pid2 = k_spawn("P1-C2", SignalJoinGlobalPid, "P1-C2", THREADS_MIN_STACK_SIZE, 3);
    printf("%s: after spawn of child with pid %d\n", testName, pid2);

    printf("%s: wait on child process\n", testName);
    kidpid = k_wait(&status);
    printf("%s: exit status for child %d is %d\n", testName, kidpid, status);

    printf("%s: wait on child process\n", testName);
    kidpid = k_wait(&status);

    printf("%s: exit status for child %d is %d\n", testName, kidpid, status);
    return 0;
}

int SpawnDumpProcess2(char* strArgs)
{
    int kid_pid;
    int status = 0xff;
    char nameBuffer[1024];

    if (strArgs != NULL)
    {
        printf("%s: started\n", strArgs);
        printf("%s: performing spawn of child\n", strArgs);

        snprintf(nameBuffer, sizeof(nameBuffer), "%s-C1", strArgs);
        kid_pid = k_spawn(nameBuffer, SimpleDumpExit, nameBuffer, THREADS_MIN_STACK_SIZE, 2);
        printf("%s: spawn of child returned pid = %d\n", strArgs, kid_pid);

        kid_pid = k_wait(&status);
        if (kid_pid == -1)
        {
            printf("%s: was signaled while blocked on wait()\n", nameBuffer);
        }
        else
        {
            printf("%s: wait returned kid_pid = %d, status = %d\n", nameBuffer,
                kid_pid, status);
        }
    }
    k_exit(-3);

    return 0;
}

