
#include "pch.h"
#include "THREADS.h"
#include "SchedulerTests.h"

int JoinParent(char* args);

/*********************************************************************************
*
* SchedulerTest10
* 
* Simple test case that creates one child process.
* 
* Expected Output:
* 
*********************************************************************************/
int SchedulerTest10(void *pArgs)
{
    int status=-1, pid1, kidpid=-1;
    char buffer[1028];
    char* testName = __func__;

    /* spawn one simple child process at a lower priority. */
    printf("%s: started\n", testName);
    snprintf(buffer, sizeof(buffer), "P1-C1 %d", getPid());
    pid1 = k_spawn("P1-C1", JoinParent, buffer, THREADS_MIN_STACK_SIZE, 3);
    printf("%s: after spawn of child with pid %d\n", testName, pid1);

    /* Join with the child and print the results. */
    printf("%s: waiting on child process\n", testName);
    kidpid = k_wait(&status);
    printf("%s: exit status for child %d is %d\n", testName, kidpid, status);

    k_exit(0);

    return 0;
}

int JoinParent(char *args)
{
    char szName[1024];
    int parentPid;
    int exitCode;

    sscanf_s(args, "%s %d", szName, (unsigned int)sizeof(szName), &parentPid);

    printf("%s: started\n", szName);
    printf("%s: joining parent process\n", szName);
    k_join(parentPid, &exitCode);
    printf("%s: finished joining parent process\n", szName);

    k_exit(-3);

    return 0;

}