
#include "pch.h"

typedef int (*TestFunction) (void*);

extern int (*kinit) (void*);

/* Array of all the Scheduler test processes. */
TestFunction schedulerTests[MAX_SCHEDULER_TEST_CASES];

int main(int argc, char *argv[])
{
	BOOL testsToRun[MAX_SCHEDULER_TEST_CASES];
	BOOL runAll = FALSE; 

	schedulerTests[0] = SchedulerTest00;
	schedulerTests[1] = SchedulerTest01;
	schedulerTests[2] = SchedulerTest02;
	schedulerTests[3] = SchedulerTest03;
	schedulerTests[4] = SchedulerTest04;
	schedulerTests[5] = SchedulerTest05;
	schedulerTests[6] = SchedulerTest06;
	schedulerTests[7] = SchedulerTest07;
	schedulerTests[8] = SchedulerTest08;
	schedulerTests[9] = SchedulerTest09;
	schedulerTests[10] = SchedulerTest10;
	schedulerTests[11] = SchedulerTest11;
	schedulerTests[12] = SchedulerTest12;
	schedulerTests[13] = SchedulerTest13;
	schedulerTests[14] = SchedulerTest14;
	if (argc == 1)
	{
		memset(testsToRun, 1, sizeof(testsToRun));
		runAll = TRUE;
	}
	else
	{
		memset(testsToRun, 0, sizeof(testsToRun));

		for (int i = 1; i < argc; ++i)
		{
			int testCase;

			if (sscanf_s(argv[i], "%d", &testCase) == 1)
			{
				if (testCase >= 0 && testCase < MAX_SCHEDULER_TEST_CASES)
				{
					testsToRun[testCase] = TRUE;
				}
			}
		}
	}

	/* Run every test that is not NULL. */
	for (int i = 0; i < MAX_SCHEDULER_TEST_CASES; ++i)
	{
		kinit = schedulerTests[i];

		if (kinit != NULL && testsToRun[i])
		{
			printf("---------- Running Scheduler Test: %d ----------\n", i);

			InitializeTHREADS();

			DWORD hCPU = CreateTHREADS(bootstrap, 2);

			SetDebugLevel(1);

			RunTHREADS(hCPU);

			WaitTHREADS(hCPU);

			StopTHREADS(hCPU);
			printf("---------- Completed Scheduler Test: %d ----------\n\n", i);
		}
	}

	return 0;
}
