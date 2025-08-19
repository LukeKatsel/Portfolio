typedef struct driverProc * driverProcPtr;

struct driverProc {

   driverProcPtr nextSleeping;   // pointer to the next sleeping proc in queue
   driverProcPtr nextRequest;    // pointer to the next request in queue

   int pid;

   int   wakeTime;    /* for sleep syscall */
   int   semaphore;  // sleeping semaphore
   int   beenZapped; // indicates if proc has been zapped



   /* Used for disk requests */
   int   operation;    /* DISK_READ, DISK_WRITE, DISK_SEEK, DISK_TRACKS */
   int   trackStart;    // first track to be read/written to
   int   sectorStart;   // sector to be read/written to
   int   numSectors;    // how many sectors to be read/written to
   void *diskBuf;       // buffer to hold read/write data
   int   reqSemaphore;  // request semaphore
   int   adjustedTrack; // track number adjusted for ordering the procs

};

