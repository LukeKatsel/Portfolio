#pragma once

#define LOWEST_PRIORITY   0
#define HIGHEST_PRIORITY  5

#define MAXNAME           256
#define MAXARG            256
#define MAXPROC           50

/* Kill signals */
#define SIG_TERM			15

/* Functions that will become system calls. */
extern int  k_spawn(char* name, int(*entryPoint)(void *), void* arg,
	              int stacksize, int priority);
extern int  k_wait(int* pChildExitCode);
extern int  k_join(int pid, int* pExitCode);
extern int  k_signal(int pid, int signal);
extern void	k_exit(int exitCode);

/* Additional kernel-only functions. */
extern int	getPid(void);
extern void	ps(void);
extern int	signaled(void);
extern int  block(int block_status);
extern int  unblock(int pid);
extern int  getStartTime(void);
extern void timeSlice(void);
extern void dispatcher(void);
extern int	readTime(void);
extern DWORD readClock(void);
