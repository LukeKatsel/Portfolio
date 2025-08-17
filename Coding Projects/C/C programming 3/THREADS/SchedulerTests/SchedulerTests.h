#pragma once
#include "Scheduler.h"

/* prototypes for functions used across multiple tests. */
int SimpleWaitExit(void* pArgs);
int SimpleDumpExit(void* pArgs);
int WaitForSignal(void* pArgs);

int spawnTwoHigher(char* strArgs);
int SpawnOneHigher(char* strArgs);
int SpawnTwoLower(char* strArgs);

int JoinTwoLower(char* strArgs);

int DelayAndDump(char* strArgs);

void SystemDelay(int millisTime);

extern int SchedulerTest00(void* pArgs);
extern int SchedulerTest01(void* pArgs);
extern int SchedulerTest02(void* pArgs);
extern int SchedulerTest03(void* pArgs);
extern int SchedulerTest04(void* pArgs);
extern int SchedulerTest05(void* pArgs);
extern int SchedulerTest06(void* pArgs);
extern int SchedulerTest07(void* pArgs);
extern int SchedulerTest08(void* pArgs);
extern int SchedulerTest09(void* pArgs);
extern int SchedulerTest10(void* pArgs);
extern int SchedulerTest11(void* pArgs);
extern int SchedulerTest12(void* pArgs);
extern int SchedulerTest13(void* pArgs);
extern int SchedulerTest14(void* pArgs);
extern int SchedulerTest15(void* pArgs);
extern int SchedulerTest16(void* pArgs);
extern int SchedulerTest17(void* pArgs);
extern int SchedulerTest18(void* pArgs);
extern int SchedulerTest19(void* pArgs);
extern int SchedulerTest20(void* pArgs);
extern int SchedulerTest21(void* pArgs);
extern int SchedulerTest22(void* pArgs);
extern int SchedulerTest23(void* pArgs);
extern int SchedulerTest24(void* pArgs);
extern int SchedulerTest25(void* pArgs);
extern int SchedulerTest26(void* pArgs);
extern int SchedulerTest27(void* pArgs);
extern int SchedulerTest28(void* pArgs);
extern int SchedulerTest29(void* pArgs);
extern int SchedulerTest30(void* pArgs);
extern int SchedulerTest31(void* pArgs);
extern int SchedulerTest32(void* pArgs);
extern int SchedulerTest33(void* pArgs);
extern int SchedulerTest34(void* pArgs);
extern int SchedulerTest35(void* pArgs);
extern int SchedulerTest36(void* pArgs);
extern int SchedulerTest37(void* pArgs);
extern int SchedulerCoreTest1(void* pArgs);
#define MAX_SCHEDULER_TEST_CASES 15