	#pragma once
#include <Windows.h>

/* System wide definitions and constants. */
#define THREADS_MIN_STACK_SIZE		8192

#define THREADS_CLOCK_INTERRUPT			0
#define THREADS_DISK_INTERRUPT			1
#define THREADS_TERMINAL_INTERRUPT		2
#define THREADS_MMU_INTERRUPT			3
#define THREADS_SYS_CALL_INTERRUPT		4
#define THREADS_INTERRUPT_HANDLER_COUNT	5

#define THREADS_MAX_NAME				64
#define THREADS_MAX_SYSCALLS			32

#define THREADS_MAX_DISKS               2
#define THREADS_MAX_TERMINALS			4
#define THREADS_MAX_IO_BUFFER_SIZE		1024

#define CLOCK_IRQ_PRIORITY				4

#define DEVICE_CLOCK 					THREADS_CLOCK_INTERRUPT
#define DEVICE_DISK						THREADS_DISK_INTERRUPT
#define DEVICE_TERMINAL					THREADS_TERMINAL_INTERRUPT

#define MAX_PROCESSES	50

#define PSR_INTERRUPTS          1
#define PSR_KERNEL_MODE         2
#define PSR_IRQ_MODE            4

#define CONTEXT_MODE_NORMAL     0
#define CONTEXT_MODE_BOOTSTRAP  1
#define CONTEXT_MODE_INTERRUPT  2

#define CLOCK_DEVICE 1
#define TERM_DEVICE  2
#define DISK_DEVICE  3

typedef enum
{
	OP_READ = 0,
	OP_WRITE,
	OP_FLUSH,
	OP_SEEK,
	OP_IOCTL,
	OP_OPEN,
	OP_CLOSE,
	OP_SYNC,
	OP_TRIM,
	OP_STATUS,
	OP_CONFIGURE,
	OP_MAP,
	OP_UNMAP
} OperationType;

typedef enum
{
	OP_STATUS_COMPLETE = 0,
	OP_STATUS_INPROGRESS
} OperationStatus;


typedef struct _ioRequest
{
	int				deviceType;
	int				deviceId;
	OperationType   operationType;
	OperationStatus operationStatus;
	unsigned int	control;
	int				bufferSize;
	unsigned char	buffer[THREADS_MAX_IO_BUFFER_SIZE];
} IORequest;

typedef struct _args
{
	DWORD *argPtr;
	DWORD argDword;
	int   argInt;
	char* argString;
} Arguments;

typedef struct _sysCallArgs
{
	int sysCallId;
	DWORD argDword;
	int   argInt;
	char* argString;
} SysCallArguments;


typedef void (*BootFunction) (void*);   /* function where process begins */
typedef int (*ProcFunction) (void*);   
typedef void (*IntHandler) (int, void *);   /* function where process begins */
typedef void (*SystemCall)(SysCallArguments* pArgs);

/* THREADS System initialization and start up functions. */
extern DWORD	InitializeTHREADS();
extern int		RunTHREADS();
DWORD			CreateTHREADS(int (*bootstrap)(void *), int count);
extern int		WaitTHREADS();
extern int		StopTHREADS();

/* THREADS Interface */
extern DWORD		GetPsr();
extern void			SetPsr(DWORD psr);

extern DWORD		SystemClock();

extern IntHandler*  GetInterruptHandlers();
extern SystemCall*  GetSystemCallVector();

extern LPVOID*		ContextInitialize(ProcFunction entryPoint, int stackSize, Arguments *pArgs);
extern BOOL			ContextSwitch(int mode, LPVOID nextContext);
extern void			ContextStop(LPVOID context);
extern void			ContextClose(LPVOID context);

extern int			RequestIO(IORequest* pRequest);
extern int			CompleteIO(IORequest* pRequest);

extern void			ConsoleOutput(BOOL debug, char* string, ...);
extern void			SetDebugLevel(int level);

extern void			Stop(int code);

/*************************************************************************
   bootstrap()

   Purpose - This is the first function called by THREADS on startup.

			 The function must setup the OS scheduler and primitive
			 functionality and then spawn the first two processes.

			 The first two process are the sentinel process
			 and a startup process.

			 The statup process is used to initialize additional layers
			 of the OS.  It is also used for testing the scheduler
			 functions.

   Parameters - Arguments *pArgs - these arguments are unused at this time.

   Returns - The function does not return.

   Side Effects - The effects of this function is the launching of the kernel.

 *************************************************************************/
extern int bootstrap(void* pArgs);
