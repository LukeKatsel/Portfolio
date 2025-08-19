
#include "pch.h"
#include "THREADS.h"
#include "SchedulerTests.h"


int SpawnDumpProcess(char* strArgs);
int SignalJoinGlobalPid(char* arg);

int gPid = -1;

/*********************************************************************************
*
* SchedulerTest13
* 
* Simple test case that creates one child process.
* 
* Expected Output:
* 
*********************************************************************************/
int SchedulerTest13(void *pArgs)
{
    int status = -1, pid1, pid2, kidpid = -1;
    char* testName = __func__;

    printf("%s: started\n", testName);

    pid1 = k_spawn("P1-C1", SpawnDumpProcess, "P1-C1", THREADS_MIN_STACK_SIZE, 4);
    printf("%s: after spawn of child with pid %d\n", testName, pid1);

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

int SpawnDumpProcess(char* strArgs)
{
    int kid_pid;
    int status = 0xff;
    char nameBuffer[1024];

    if (strArgs != NULL)
    {
        printf("%s: started\n", strArgs);
        printf("%s: performing spawn of child\n", strArgs);

        snprintf(nameBuffer, sizeof(nameBuffer), "%s-C1", strArgs);
        gPid = k_spawn(nameBuffer, SimpleDumpExit, nameBuffer, THREADS_MIN_STACK_SIZE, 2);
        printf("%s: spawn of child returned pid = %d\n", strArgs, gPid);

        kid_pid = k_wait(&status);
        printf("%s: wait returned kid_pid = %d, status = %d\n", strArgs,
            kid_pid, status);
    }
    k_exit(-3);

    return 0;
}

int SignalJoinGlobalPid(char* arg)
{
    int exitCode;

    if (arg != NULL)
    {
        printf("%s: started\n", arg);
        printf("%s: signalling %d.\n", arg, gPid);
        k_signal(gPid, SIG_TERM);
        printf("%s: joining %d.\n", arg, gPid);
        k_join(gPid, &exitCode);
        printf("%s: after joining child, pid %d, status = %d\n", arg, gPid, exitCode);
    }

    k_exit(5);
    return 0;
}
