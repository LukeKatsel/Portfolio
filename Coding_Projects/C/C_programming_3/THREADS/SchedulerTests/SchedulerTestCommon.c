#include "pch.h"

/* prototypes for functions used across multiple tests. */
int SimpleWaitExit(void* pArgs);
int spawnTwoHigher(char* pArgs);
int DelayAndDump(char* arg);
int JoinTwoLower(char* strArgs);


void SystemDelay(int millisTime)
{
    int startTime;

    startTime = readClock();
    while (((int)readClock() - startTime) < millisTime);
}


int DelayAndDump(char* arg)
{
    unsigned long startTime, currentTime;
    int printingThread = 0;
    unsigned long printAt = 3000;
    unsigned long stopAt = 10000;
    char* testName = __func__;

    printf("%s: started\n", arg);

    if (arg != NULL && (arg[strlen(arg) - 1] == '1' || arg[strlen(arg) - 1] == '5'))
    {
        printingThread = 1;
    }

    startTime = readClock();
    while (1)
    {
        currentTime = readClock();

        if (printingThread && (currentTime - startTime) > printAt)
        {
            printf("Time Elapsed: %d\n", currentTime - startTime);
            printingThread = 0;
            ps();
        }
        else if ((currentTime - startTime) > stopAt)
        {
            break;
        }

    }
    printf("%s: exitting, pid = %d\n", arg, getPid());
    k_exit(-getPid());
    return 0;
}


int SimpleWaitExit(void* pArgs)
{
    if (pArgs != NULL)
    {
        printf("%s: started\n", (char*)pArgs);
        SystemDelay(10);
        printf("%s: quitting\n", (char*)pArgs);
    }

    k_exit(-3);

    return 0;
}

int WaitForSignal(void* pArgs)
{
    if (pArgs != NULL)
    {
        printf("%s: started\n", (char*)pArgs);
        while (!signaled())
        {
        }
        printf("%s: quitting\n", (char*)pArgs);
    }

    k_exit(-3);

    return 0;
}

int SimpleDumpExit(void* pArgs)
{
    if (pArgs != NULL)
    {
        printf("%s: started\n", (char*)pArgs);
        ps();
        printf("%s: quitting\n", (char*)pArgs);
    }

    k_exit(-3);

    return 0;
}


int spawnTwoHigher(char* strArgs)
{
    int kid_pid;
    int status = 0xff;
    char nameBuffer[1024];

    if (strArgs != NULL)
    {
        printf("%s: started\n", strArgs);
        printf("%s: performing spawn of first child\n", strArgs);

        snprintf(nameBuffer, sizeof(nameBuffer), "%s-C1", strArgs);
        kid_pid = k_spawn(nameBuffer, SimpleWaitExit, nameBuffer, THREADS_MIN_STACK_SIZE, 4);
        printf("%s: spawn of first child returned pid = %d\n", strArgs, kid_pid);

        snprintf(nameBuffer, sizeof(nameBuffer), "%s-C2", strArgs);
        printf("%s: performing spawn of second child\n", strArgs);
        kid_pid = k_spawn(nameBuffer, SimpleWaitExit, nameBuffer, THREADS_MIN_STACK_SIZE, 4);
        printf("%s: spawn of second child returned pid = %d\n", strArgs, kid_pid);

        kid_pid = k_wait(&status);
        printf("%s: first wait returned kid_pid = %d, status = %d\n", strArgs,
            kid_pid, status);

        kid_pid = k_wait(&status);
        printf("%s: second wait returned kid_pid = %d, status = %d\n", strArgs,
            kid_pid, status);
    }
    k_exit(-3);

    return 0;
}

int SpawnTwoLower(char* strArgs)
{
    int kid_pid;
    int status = 0xff;
    char nameBuffer[1024];

    if (strArgs != NULL)
    {
        printf("%s: started\n", strArgs);
        printf("%s: performing spawn of first child\n", strArgs);

        snprintf(nameBuffer, sizeof(nameBuffer), "%s-C1", strArgs);
        kid_pid = k_spawn(nameBuffer, SimpleWaitExit, nameBuffer, THREADS_MIN_STACK_SIZE, 2);
        printf("%s: spawn of first child returned pid = %d\n", strArgs, kid_pid);

        snprintf(nameBuffer, sizeof(nameBuffer), "%s-C2", strArgs);
        printf("%s: performing spawn of second child\n", strArgs);
        kid_pid = k_spawn(nameBuffer, SimpleWaitExit, nameBuffer, THREADS_MIN_STACK_SIZE, 2);
        printf("%s: spawn of second child returned pid = %d\n", strArgs, kid_pid);

        kid_pid = k_wait(&status);
        printf("%s: first wait returned kid_pid = %d, status = %d\n", strArgs,
            kid_pid, status);

        kid_pid = k_wait(&status);
        printf("%s: second wait returned kid_pid = %d, status = %d\n", strArgs,
            kid_pid, status);
    }
    k_exit(-3);

    return 0;
}
int SpawnOneHigher(char* strArgs)
{
    int kid_pid;
    int status = 0xff;
    char nameBuffer[1024];

    if (strArgs != NULL)
    {
        printf("%s: started\n", strArgs);
        printf("%s: performing spawn of child\n", strArgs);

        snprintf(nameBuffer, sizeof(nameBuffer), "%s-C1", strArgs);
        kid_pid = k_spawn(nameBuffer, SimpleWaitExit, nameBuffer, THREADS_MIN_STACK_SIZE, 4);
        printf("%s: spawn of child returned pid = %d\n", strArgs, kid_pid);

        kid_pid = k_wait(&status);
        printf("%s: join returned kid_pid = %d, status = %d\n", strArgs,
            kid_pid, status);
    }
    k_exit(-3);

    return 0;
}


