/*
Phase 4 of USLOSS project for CSCV 452
Luke Katsel
*/

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <usloss.h>
#include <phase1.h>
#include <phase2.h>
#include <phase3.h>
#include <phase4.h>
#include <usyscall.h>
#include <provided_prototypes.h>
#include "driver.h"

int DEBUG4 = 0;
int debugflag4 = 0;

static int running; /*semaphore to synchronize drivers and start3*/

static int diskpids[DISK_UNITS]; // process ids for the disks

static struct driverProc DriverTable[MAXPROC]; // process table

driverProcPtr sleepingQueue;    //queue for procs that have been put to sleep
driverProcPtr requestQueue[DISK_UNITS]; // queue for procs that have a read/write/seek request
int requestQueueSem[DISK_UNITS];    // semaphore for request queue
int diskSemaphore[DISK_UNITS];  // semaphore for disks
int *num_tracks[DISK_UNITS];    // used to count the number of disk tracks

int endDisk;  // flag to indicate that disk should terminate

static int	ClockDriver(char *);
static int	DiskDriver(char *);

static void sleep(sysargs *arg);
int  sleep_real(int seconds);

static void diskRead(sysargs *arg);
int  disk_read_real(int unit, int track, int first, int sectors, void *buffer);

static void diskWrite(sysargs *arg);
int  disk_write_real(int unit, int track, int first, int sectors, void *buffer);

static void diskSize(sysargs *arg);
int  disk_size_real(int unit, int *sector, int *track, int *disk);

int  term_read_real(int unit, int size, char *buffer); // ?
int  term_write_real(int unit, int size, char *text); // ?

void checkKernelMode(void);
void addToRequestQueue(int unit, struct driverProc request);

int start3(char *arg){

    char	name[128];
    int		i;
    int		clockPID;
    int		status;

    /*
     * Check kernel mode here.
     */
    checkKernelMode();

    /* Assignment system call handlers */
    sys_vec[SYS_SLEEP]      = sleep;
    sys_vec[SYS_DISKREAD]   = diskRead;
    sys_vec[SYS_DISKWRITE]  = diskWrite;
    sys_vec[SYS_DISKSIZE]   = diskSize;

    /* Initialize the phase 4 process table */
    for (int i = 0; i < MAXPROC; i++){

        DriverTable[i].nextSleeping = NULL;
        DriverTable[i].nextRequest = NULL;
        DriverTable[i].pid = -1;
        DriverTable[i].wakeTime = -1;
        DriverTable[i].semaphore = semcreate_real(0);
        DriverTable[i].beenZapped = 0;
        DriverTable[i].operation = -1;
        DriverTable[i].trackStart = -1;
        DriverTable[i].sectorStart = -1;
        DriverTable[i].numSectors = -1;
        DriverTable[i].diskBuf = NULL;
        DriverTable[i].reqSemaphore = semcreate_real(0);
        DriverTable[i].adjustedTrack = -1;
    }

    sleepingQueue = NULL;
    endDisk = 0;

    /*
     * Create clock device driver 
     * I am assuming a semaphore here for coordination.  A mailbox can
     * be used instead -- your choice.
     */
    running = semcreate_real(0);

    clockPID = fork1("Clock driver", ClockDriver, NULL, USLOSS_MIN_STACK, 2);

    if (clockPID < 0) {

	    console("start3(): Can't create clock driver\n");
	    halt(1);
    }
    /*
     * Wait for the clock driver to start. The idea is that ClockDriver
     * will V the semaphore "running" once it is running.
     */

    semp_real(running);

    /*
     * Create the disk device drivers here.  You may need to increase
     * the stack size depending on the complexity of your
     * driver, and perhaps do something with the pid returned.
     */
    char buf[10];

    
    for (i = 0; i < DISK_UNITS; i++) {  // loop to spawn both disks

        sprintf(buf, "%d", i);
        sprintf(name, "DiskDriver%d", i);

        diskpids[i] = fork1(name, DiskDriver, buf, USLOSS_MIN_STACK, 2);

        if (diskpids[i] < 0) {

           console("start3(): Can't create disk driver %d\n", i);
           halt(1);
        }
        
        semp_real(running);
    }

    /*
     * Create first user-level process and wait for it to finish.
     * These are lower-case because they are not system calls;
     * system calls cannot be invoked from kernel mode.
     * I'm assuming kernel-mode versions of the system calls
     * with lower-case names.
     */
    int pid;
    pid = spawn_real("start4", start4, NULL,  8 * USLOSS_MIN_STACK, 3);
    pid = wait_real(&status);

    /*
     * Zap the device drivers
     */
    zap(clockPID);  // clock driver
    join(&status); /* for the Clock Driver */

    endDisk = 1;
    semv_real(diskSemaphore[DISK_UNITS - 2]);
    zap (diskpids[DISK_UNITS - 2]);
    join(&status);

    semv_real(diskSemaphore[DISK_UNITS - 1]);
    zap (diskpids[DISK_UNITS - 1]);
    join(&status);

    quit(0);
}

static int ClockDriver(char *arg){

    int result;
    int status;
    int curTime;

    /*
     * Let the parent know we are running and enable interrupts.
     */

    semv_real(running);
    psr_set(psr_get() | PSR_CURRENT_INT);

    while (! is_zapped()) {

	    result = waitdevice(CLOCK_DEV, 0, &status);

	    if (result != 0) {
	        return 0;
	    }
        /*
        * Compute the current time and wake up any processes
        * whose time has come.
        */
        curTime = sys_clock();
        // while there is somthing to wake
        while (sleepingQueue != NULL && sleepingQueue->wakeTime < curTime){
            
            semv_real(sleepingQueue->semaphore);
            // proc to retain next sleeping proc
            driverProcPtr nextProc = sleepingQueue->nextSleeping;
            // initialize woken proc
            sleepingQueue->nextSleeping = NULL;
            sleepingQueue->wakeTime = -1;
            sleepingQueue = nextProc;
        }
    }
    return 0;
}

static void sleep(sysargs *arg){

    if (DEBUG4 && debugflag4){

        console("sleep():");
    }

    // pass the seconds to sleep_real
    int seconds = arg->arg1;

    // sleep_real will do the work 
    if (sleep_real(seconds) != 0){
        // error
    }

    //user mode
    psr_set(psr_get() & ~PSR_CURRENT_MODE);
}

int sleep_real(int seconds){

    int curTime;

    if (DEBUG4 && debugflag4){

        console("sleep_real():");
    }

    checkKernelMode();

    // argument validation
    if (seconds < 0){

        return -1;
    }

    curTime = sys_clock();

    // pid for proc table entry
    int pid = getpid() % MAXPROC;

    // variable to hold the time it should wake
    int wakeTime = curTime + (seconds * 1000000);

    // set time when proc needs to wake up
    DriverTable[pid].wakeTime = wakeTime;

    // put the proc in the sleeping queue
    if (sleepingQueue == NULL){
        //nothing else in queue
        sleepingQueue = &DriverTable[pid];
    }
    else if (sleepingQueue->wakeTime > wakeTime){
        // put new proc first in queue
        DriverTable[pid].nextSleeping = sleepingQueue;
        sleepingQueue = &DriverTable[pid];
    }
    else{

        //proc ptr to point to last proc in loop
        driverProcPtr lastProc = NULL;

        // proc ptr to use for looping
        driverProcPtr loopProc = sleepingQueue;

        // loop through queue till we find the proper spot or until we reach end
        while (loopProc != NULL && loopProc->wakeTime < wakeTime){
            // need to find procs that we fall between
            lastProc = loopProc;
            loopProc = loopProc->nextSleeping;
        }

        // proc that will wake before new one points to it
        lastProc->nextSleeping = &DriverTable[pid];
        
        // new proc points to the proc that will wake after it
        DriverTable[pid].nextSleeping = loopProc;
    }

    semp_real(DriverTable[pid].semaphore);
}

/*  Disk Driver     */
static int DiskDriver(char *arg){

    int unit = atoi(arg);
    device_request myRequest;
    int result;
    int status;
    int i;

    driverProcPtr current_req;

    // initialize queue and semaphore
    requestQueue[unit] = NULL;
    requestQueueSem[unit] = semcreate_real(1);
    diskSemaphore[unit] = semcreate_real(0);

    if (DEBUG4 && debugflag4)
      console("DiskDriver(%d): started\n", unit);

    // we are running
    semv_real(running);

   /* Get the number of tracks for this disk */
    int *num;

    myRequest.opr  = DISK_TRACKS;
    myRequest.reg1 = &num;

    result = device_output(DISK_DEV, unit, &myRequest);

    if (result != DEV_OK) {
        console("DiskDriver %d: did not get DEV_OK on DISK_TRACKS call\n", unit);
        console("DiskDriver %d: is the file disk%d present???\n", unit, unit);
        halt(1);
    }

    waitdevice(DISK_DEV, unit, &status);
    // num_tracks holds number of tracks for each disk
    num_tracks[unit] = num;

    if (DEBUG4 && debugflag4){

        console("DiskDriver(%d): tracks = %d\n", unit, num_tracks[unit]);
    }

    // while not zapped and not flagged to end disk proc
    while (!is_zapped() && endDisk != 1) {

        // disk semaphore
        semp_real(diskSemaphore[unit]);
        
        if (endDisk == 1){
            // if flagged to end
            break;
        }
        // queue semaphore
        semp_real(requestQueueSem[unit]);

        // ptr to the request
        driverProcPtr request = requestQueue[unit];

        if (requestQueue[unit] != NULL){
            // if theres somthing in the queue
            requestQueue[unit] = requestQueue[unit]->nextRequest;
        }

        // request validation
        if (request->trackStart >= &num_tracks[unit]){
            console("DiskDriver() too many tracks");
            halt(1);
        }

        // prepare for request
        myRequest.opr = DISK_SEEK;
        myRequest.reg1 = request->trackStart;
        result = device_output(DISK_DEV, unit, &myRequest);

        if (result != DEV_OK) {
            console("DiskDriver %d: did not get DEV_OK on DISK_TRACKS call\n", unit);
            console("DiskDriver %d: is the file disk%d present???\n", unit, unit);
            halt(1);
        }

        //wait on device
        waitdevice(DISK_DEV, unit, &status);
        if (status != 0){

            console("DiskDriver() waitDevice error");
        }

        /*execute requests*/

        // loop # of sectors times
        for (i = 0; i < request->numSectors; i++){
            
            // set myRequest with request info
            myRequest.opr = request->operation;
            myRequest.reg1 = (request->sectorStart + i) % DISK_TRACK_SIZE; // more than DISK_TRACK_SIZE?
            myRequest.reg2 = &request->diskBuf[i * DISK_SECTOR_SIZE];
            // make request
            result = device_output(DISK_DEV, unit, &myRequest);

            if (result != DEV_OK) {
                console("DiskDriver %d: did not get DEV_OK on DISK_TRACKS call\n", unit);
                console("DiskDriver %d: is the file disk%d present???\n", unit, unit);
                halt(1);
            }

            //wait on device
            waitdevice(DISK_DEV, unit, &status);
            if (status != 0){

                console("DiskDriver() waitDevice error");
            }
        }

        // release queue semaphore
        semv_real(requestQueueSem[unit]);

        //wake process indicated by the request's pid field 
        semv_real(DriverTable[request->pid].reqSemaphore);
    }

    return 0;
}


static void diskRead(sysargs *arg){

    void *diskBuf = arg->arg1;
    int unit = arg->arg5;
    int track = arg->arg3;
    int sector = arg->arg4;
    int numSectors = arg->arg2;

    // actually read from the given area
    int status = disk_read_real(unit, track, sector, numSectors, diskBuf);

    // set the status arg and return arg
    if (status == -1){
        arg->arg1 = (void *) 1;
    }
    arg->arg4 = (void *) status;
    arg->arg1 = (void *) status;

    //user mode
    psr_set(psr_get() & ~PSR_CURRENT_MODE);

}

int  disk_read_real(int unit, int track, int first, int sectors, void *buffer){

    checkKernelMode();

    // input validation 
    if (unit > DISK_UNITS || unit < 0){
        // disk number too high or low
        return -1;
    }
    if (track > DISK_TRACK_SIZE || track < 0){
        // number of track too high or low
        return -1;
    }
    if (first > DISK_TRACK_SIZE || first < 0){
        // first sector is too high or low
        return -1;
    }

    // update process in process table with the request info
    DriverTable[getpid() % MAXPROC].pid = getpid();
    DriverTable[getpid() % MAXPROC].diskBuf = buffer;
    DriverTable[getpid() % MAXPROC].operation = DISK_READ;
    DriverTable[getpid() % MAXPROC].trackStart = track;
    DriverTable[getpid() % MAXPROC].sectorStart = first;
    DriverTable[getpid() % MAXPROC].numSectors = sectors;
    DriverTable[getpid() % MAXPROC].nextRequest = NULL;

    // add the proc to the request queue
    addToRequestQueue(unit, DriverTable[getpid() % MAXPROC]);
    // lock semaphore
    semp_real(DriverTable[getpid() % MAXPROC].reqSemaphore);
    return 0;
}

static void diskWrite(sysargs *arg){

    void *diskBuf = arg->arg1;
    int unit = arg->arg5;
    int track = arg->arg3;
    int sector = arg->arg4;
    int numSectors = arg->arg2;

    // write to the specified area
    int status = disk_write_real(unit, track, sector, numSectors, diskBuf);

    // set the status arg and return arg
    if (status == -1){
        arg->arg1 = (void *) 1;
    }
    arg->arg4 = (void *) status;
    arg->arg1 = (void *) status;

    //user mode
    psr_set(psr_get() & ~PSR_CURRENT_MODE);
}

int  disk_write_real(int unit, int track, int first, int sectors, void *buffer){

    checkKernelMode();

    // input validation 
    if (unit > DISK_UNITS || unit < 0){
        // disk number is too high or low
        return -1;
    }
    if (track > DISK_TRACK_SIZE || track < 0){
        // the specified track does not exist
        return -1;
    }
    if (first > DISK_TRACK_SIZE || first < 0){
        // the first sector does not exist
        return -1;
    }

    // initalize proc table entry with writing request
    DriverTable[getpid() % MAXPROC].pid = getpid();
    DriverTable[getpid() % MAXPROC].diskBuf = buffer;
    DriverTable[getpid() % MAXPROC].operation = DISK_WRITE;
    DriverTable[getpid() % MAXPROC].trackStart = track;
    DriverTable[getpid() % MAXPROC].sectorStart = first;
    DriverTable[getpid() % MAXPROC].numSectors = sectors;
    DriverTable[getpid() % MAXPROC].nextRequest = NULL;

    // add the request to the queue
    addToRequestQueue(unit, DriverTable[getpid() % MAXPROC]);
    // lock request semaphore
    semp_real(DriverTable[getpid() % MAXPROC].reqSemaphore);
    return 0;
}

static void diskSize(sysargs *arg){

    // que up for size check
    int unit = arg->arg1;
    int sector;
    int track;
    int disk;

    // do the size check
    if (disk_size_real(unit, &sector, &track, &disk) == -1){

        console("diskSize() disk_size_real error");
    }

    // move the results to arg
    arg->arg1 = (void *)sector;
    arg->arg2 = (void *)track;
    arg->arg3 = (void *)disk;


    //user mode
    psr_set(psr_get() & ~PSR_CURRENT_MODE);
}

int  disk_size_real(int unit, int *sector, int *track, int *disk){

    checkKernelMode();

    // input validation 
    if (unit > DISK_UNITS || unit < 0){
        console("disk_size_real() unit size wrong");
        return -1;
    }

    // disk number is valid so pass the info
    *sector = DISK_SECTOR_SIZE;
    *track = DISK_TRACK_SIZE;
    *disk = DISK_TRACK_SIZE + DISK_TRACK_SIZE * unit; 

    return 0;
}

void checkKernelMode(void){

    if (PSR_CURRENT_MODE && psr_get() == 0){

        console("Not in Kernel Mode Halting...\n");
        halt(1);
    }
}

void addToRequestQueue(int unit, struct driverProc request){

    // input validation 
    if (unit > DISK_UNITS || unit < 0){
        console("addToRequestQueue() unit size wrong");
    }

    // lock disk semaphore
    semp_real(requestQueueSem[unit]);

    if (requestQueue[unit] == NULL){

        // Queue is empty so add to top
        requestQueue[unit] = &DriverTable[request.pid % MAXPROC];
        requestQueue[unit]->adjustedTrack = 0;
    }
    else{
        //proc ptr to point to last proc in loop
        driverProcPtr lastProc = NULL;

        // proc ptr to use for looping
        driverProcPtr loopProc = requestQueue[unit];

        // algorithm to place into queue in corect order.
        if  (requestQueue[unit]->trackStart != 0){
            // do not need to adjust track number if first track
            if (request.trackStart >= requestQueue[unit]->trackStart){
                // if the track is higher than the first one in queue then 
                // we need to substract from it
                request.adjustedTrack = request.trackStart - requestQueue[unit]->trackStart;
            }
            else{
                // if its lower then we need to add to it
                request.adjustedTrack = request.trackStart + (DISK_TRACK_SIZE - requestQueue[unit]->trackStart);
            }
        }
        else{
            // if the first track set the adjusted track to the starting track
            request.adjustedTrack = request.trackStart;
        }
        // update proc table entry with adjusted track
        DriverTable[request.pid % MAXPROC].adjustedTrack = request.adjustedTrack;

        // loop through queue till we find closest track or until we reach end
        while (loopProc != NULL && loopProc->adjustedTrack <= request.adjustedTrack){

            lastProc = loopProc;
            loopProc = loopProc->nextRequest;
        }

        if (lastProc == NULL){
            // then this is the first request in queue
            requestQueue[unit] = &DriverTable[request.pid % MAXPROC];
        }
        else{
            // proc that will wake before new one points to it
            lastProc->nextRequest = &DriverTable[request.pid % MAXPROC];
        }
        // set the next request to the one after new one
        DriverTable[request.pid % MAXPROC].nextRequest = loopProc;
    }

    //release the queue semaphore
    semv_real(requestQueueSem[unit]);
    //release the disk semaphore
    semv_real(diskSemaphore[unit]);

}