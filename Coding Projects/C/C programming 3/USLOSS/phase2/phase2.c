/* ------------------------------------------------------------------------
   phase2.c
   Applied Technology
   College of Applied Science and Technology
   The University of Arizona
   CSCV 452

   ------------------------------------------------------------------------ */
#include <stdlib.h>
#include <string.h>
#include <phase1.h>
#include <phase2.h>
#include <usloss.h>
#include "message.h"

/* ------------------------- Prototypes ----------------------------------- */
int start1 (char *);
extern int start2 (char *);
static void enableInterrupts(void);
static void disableInterrupts(void);
static void check_kernel_mode(char procName[MAXNAME]);
static int GetNextEmptyMailbox();
void blockProcess(int blockStatus, int mbox_id, void *msg_ptr, int msg_size);
int unblockProcess(int blockStatus, int mbox_id, void *msg_ptr, int msg_size);
void deliverMsg(int mbox_id, void *msg_ptr, int msg_size);
int grabMsg(int mbox_id, void *msg_ptr, int msg_size);
static void nullsys(sysargs *arg);
static void clockInterrupt(int dev, void *arg);
static void diskInterrupt(int dev, void *arg);
static void terminalInterrupt(int dev, void *arg);
static void systemcallInterrupt(int dev, void *arg);

/* -------------------------- Globals ------------------------------------- */

int debugflag2 = 0;

void (*sys_vec[MAXSYSCALLS])(sysargs *args);


/* the mail boxes */
mail_box ClockMail;
mail_box TerminalMail[TERM_UNITS];
mail_box DiskMail[DISK_UNITS];

mail_box MailBoxTable[MAXMBOX];
int OpenMailSlots;
static int nextMailboxId = 0;
int DeviceCounter = 0;
int ClockCounter = 0;

int BlockPid = -1;


/* -------------------------- Functions -----------------------------------*/

/* ------------------------------------------------------------------------
   Name - start1
   Purpose - Initializes mailboxes and interrupt vector.
             Start the phase2 test process.
   Parameters - one, default arg passed by fork1, not used here.
   Returns - one to indicate normal quit.
   Side Effects - lots since it initializes the phase2 data structures.
   ----------------------------------------------------------------------- */
int start1(char *arg)
{
   int kid_pid, status, i; 

   if (DEBUG2 && debugflag2)
      console("start1(): at beginning\n");

   check_kernel_mode("start1");

   /* Disable interrupts */
   disableInterrupts();

   /* Initialize other data structures.
    Initialize int_vec and sys_vec, allocate mailboxes for interrupt
    handlers.  Etc... */
   
   // Initialize the mail box table
   for(i = 0; i < MAXMBOX - 1; i++){

      MailBoxTable[i].mbox_id = i;
      MailBoxTable[i].status = MBSTATUS_INACTIVE;
      MailBoxTable[i].numSlots = 0;
      MailBoxTable[i].fullSlots = 0;
      MailBoxTable[i].slotSize = 0;
      MailBoxTable[i].numWaitSendProc = 0;
      MailBoxTable[i].numWaitReceiveProc = 0;
      MailBoxTable[i].waitingSendProc = NULL;
      MailBoxTable[i].waitingReceiveProc= NULL;
      MailBoxTable[i].headSlotPtr = NULL;
      MailBoxTable[i].openSlot = MailBoxTable[i].headSlotPtr;
   }

   // Initialize the slots tracker
   OpenMailSlots = MAXSLOTS;

   // system call interrupt initialization
   int_vec[SYSCALL_INT] = systemcallInterrupt;

   for (i = 0; i < MAXSYSCALLS; i++){
      
      sys_vec[i] = nullsys;
   }

   // clock interrupt initialization
   int_vec[CLOCK_INT] = clockInterrupt;

   ClockMail = MailBoxTable[MboxCreate(0, sizeof(int))];

   // disk interrupt initialization
   int_vec[DISK_INT] = diskInterrupt;

   for (i = 0; i < DISK_UNITS; i++){
      
      DiskMail[i] = MailBoxTable[MboxCreate(0, sizeof(int))];
   }

   // terminal interrupt initialization
   int_vec[TERM_INT] = terminalInterrupt;

   for (i = 0; i < TERM_UNITS; i++){
      
      TerminalMail[i] = MailBoxTable[MboxCreate(0, sizeof(int))];
   }

   enableInterrupts();

   /* Create a process for start2, then block on a join until start2 quits */
   if (DEBUG2 && debugflag2)
      console("start1(): fork'ing start2 process\n");
   kid_pid = fork1("start2", start2, NULL, 4 * USLOSS_MIN_STACK, 1);
   if ( join(&status) != kid_pid ) {
      console("start2(): join returned something other than start2's pid\n");
   }

   return 0;
} /* start1 */


/* ------------------------------------------------------------------------
   Name - MboxCreate
   Purpose - gets a free mailbox from the table of mailboxes and initializes it 
   Parameters - maximum number of slots in the mailbox and the max size of a msg
                sent to the mailbox.
   Returns - -1 to indicate that no mailbox was created, or a value >= 0 as the
             mailbox id.
   Side Effects - initializes one element of the mail box array. 
   ----------------------------------------------------------------------- */
int MboxCreate(int slots, int slot_size){

   int emptyMbox, i;

   check_kernel_mode("MboxCreate");

   /* Disable interrupts */
   disableInterrupts();

   if ((emptyMbox = GetNextEmptyMailbox()) == -1){
      // all mailboxes full
      if (DEBUG2 && debugflag2){
         console("MboxCreate: All mailboxes are full. \n");
      }
      enableInterrupts();
      return -1;
   }

   else{
      // initialize the slot info
      MailBoxTable[emptyMbox].status = MBSTATUS_ACTIVE;
      MailBoxTable[emptyMbox].numSlots = slots;
      MailBoxTable[emptyMbox].slotSize = slot_size;

      slot_ptr currentSlot;
      // make sure slot size is valid
      if (slots != 0 && slot_size > 0 && slot_size < MAX_MESSAGE){

         MailBoxTable[emptyMbox].slotSize = slot_size;

         slot_ptr newSlots[slots];

         for (i = 0; i < slots; i++) {
            // allocate memory for new slots
            newSlots[i] = (slot_ptr)malloc(sizeof(mail_slot));
         }

         currentSlot = MailBoxTable[emptyMbox].headSlotPtr = newSlots[0];
         // the next open slot is the head slot
         MailBoxTable[emptyMbox].openSlot = MailBoxTable[emptyMbox].headSlotPtr;
         // add the slots into the linked list
         for(i = 1; i < slots; i++){

            currentSlot->nextSlotPtr = newSlots[i];
            currentSlot = currentSlot->nextSlotPtr;
         }
      }

      if (slot_size < 0 || slot_size > MAX_MESSAGE){
         // slot size wrong
         if (DEBUG2 && debugflag2){
            console("MboxCreate: Slot_size is wrong. \n");
         }
         enableInterrupts();
         return -1;
      }
      
      enableInterrupts();
      //return MailBoxTable[emptyMbox].mbox_id;
      return nextMailboxId; 
   }
} /* MboxCreate */

/* ------------------------------------------------------------------------
   Name - MboxSend
   Purpose - Put a message into a slot for the indicated mailbox.
             Block the sending process if no slot available.
   Parameters - mailbox id, pointer to data of msg, # of bytes in msg.
   Returns - zero if successful, -1 if invalid args.
   Side Effects - none.
   ----------------------------------------------------------------------- */
int MboxSend(int mbox_id, void *msg_ptr, int msg_size){

   check_kernel_mode("MboxSend");

   /* Disable interrupts */
   disableInterrupts();

   // error checking for mbox_id
   if ((MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE) || mbox_id > 1999 || mbox_id < 0){
      // invalid mailbox id
      if (DEBUG2 && debugflag2){
         console("MboxSend: invalid mailbox id. \n");
      }
      enableInterrupts();
      return -1;
   }

   // error checking for msg_size
   if (msg_size > MailBoxTable[mbox_id].slotSize || msg_size > MAX_MESSAGE){
      // msg size invalid
      if (DEBUG2 && debugflag2){
         console("MboxSend: msg size invalid. \n");
      }
      enableInterrupts();
      return -1;
   }
   // 0 slot mailbox 
   if (MailBoxTable[mbox_id].numSlots == 0){

      // check if another process is blocked to receive on this box
      if (MailBoxTable[mbox_id].numWaitReceiveProc == 0){
         // if nothing waiting - block process
         blockProcess(BLOCKSEND, mbox_id, msg_ptr, msg_size);
      }
      else{
         // if somthing is waiting to receive - unblock it
         if (unblockProcess(BLOCKRECEIVE, mbox_id, msg_ptr, msg_size) == -1){
            if (DEBUG2 && debugflag2){
               console("MboxSend: size not right. \n");
            }
            enableInterrupts();
            return -1;
         } 
      }

      if (is_zapped()){
         //process was zapped
         if (DEBUG2 && debugflag2){
            console("MboxSend: proc was zapped. \n");
         }
         enableInterrupts();
         return -3;
      }

      if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
         // mailbox became inactive
         if (DEBUG2 && debugflag2){
            console("MboxReceive: mailbox became inactive. \n");
         }
         if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){
            
            unblockProcess(BLOCKRECEIVE, mbox_id, NULL, 0);
         }
         else if (MailBoxTable[mbox_id].numWaitSendProc > 0){

            unblockProcess(BLOCKSEND, mbox_id, NULL, 0);
         }
         else{

            if (BlockPid != 0){
               unblock_proc(BlockPid);
            }
         }
         
         enableInterrupts();
         return -3;
      }
      enableInterrupts();
      return 0;
   }

   // no open slots - all slots full
   if (MailBoxTable[mbox_id].numSlots == MailBoxTable[mbox_id].fullSlots){

      blockProcess(BLOCKSEND, mbox_id, msg_ptr, msg_size);

      if (is_zapped()){
         //process was zapped
         if (DEBUG2 && debugflag2){
            console("MboxSend: proc was zapped. \n");
         }
         enableInterrupts();
         return -3;
      }

      if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
         // mailbox became inactive
         if (DEBUG2 && debugflag2){
            console("MboxReceive: mailbox became inactive. \n");
         }
         if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){
            
            unblockProcess(BLOCKRECEIVE, mbox_id, NULL, 0);
         }
         else if (MailBoxTable[mbox_id].numWaitSendProc > 0){

            unblockProcess(BLOCKSEND, mbox_id, NULL, 0);
         }
         else{

            if (BlockPid != 0){
               unblock_proc(BlockPid);
            }
         }
         
         enableInterrupts();
         return -3;
      }

   }

   // place the msg in the slot
   deliverMsg(mbox_id, msg_ptr, msg_size);


   // now that there is a msg in slot 
   // we can unblock any waiting procs
   if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){
      if (unblockProcess(BLOCKRECEIVE, mbox_id, msg_ptr, msg_size) == -1){
         if (DEBUG2 && debugflag2){
            console("MboxSend: size not right. \n");
         }
         enableInterrupts();
         return -1;
      } 
   }

   if (is_zapped()){
      //process was zapped
      if (DEBUG2 && debugflag2){
         console("MboxSend: proc was zapped. \n");
      }
      enableInterrupts();
      return -3;
   }

   if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
      // mailbox became inactive
      if (DEBUG2 && debugflag2){
         console("MboxSend: mailbox became inactive. \n");
      }
      enableInterrupts();
      return -3;
   }

   enableInterrupts();
   return 0;

} /* MboxSend */

/* ------------------------------------------------------------------------
   Name - MboxReceive
   Purpose - Get a msg from a slot of the indicated mailbox.
             Block the receiving process if no msg available.
   Parameters - mailbox id, pointer to put data of msg, max # of bytes that
                can be received.
   Returns - actual size of msg if successful, -1 if invalid args.
   Side Effects - none.
   ----------------------------------------------------------------------- */
int MboxReceive(int mbox_id, void *msg_ptr, int msg_size){

   int retVal = 0;

   check_kernel_mode("MboxReceive");

   /* Disable interrupts */
   disableInterrupts();

   // error checking for mbox_id
   if ((MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE) || mbox_id > 1999 || mbox_id < 0){
      // invalid mailbox id
      if (DEBUG2 && debugflag2){
         console("MboxReceive: invalid mailbox id. \n");
      }
      enableInterrupts();
      return -1;
   }

   // error checking for msg_size
   if (msg_size > MAX_MESSAGE){
      // msg size invalid
      if (DEBUG2 && debugflag2){
         console("MboxReceive: msg size invalid. \n");
      }
      enableInterrupts();
      return -1;
   }

   // 0 slot mailbox
   if (MailBoxTable[mbox_id].numSlots == 0){

      // check if another process is blocked to send on this box
      if (MailBoxTable[mbox_id].numWaitSendProc == 0){
         // if nothing waiting - block process
         blockProcess(BLOCKRECEIVE, mbox_id, msg_ptr, msg_size);
      }
      else{
         // if somthing is waiting to send - unblock it
         retVal = unblockProcess(BLOCKSEND, mbox_id, msg_ptr, msg_size);
            
      }

      if (is_zapped()){
         //process was zapped
         if (DEBUG2 && debugflag2){
            console("MboxReceive: proc was zapped. \n");
         }
         enableInterrupts();
         return -3;
      }

      if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
         // mailbox became inactive
         if (DEBUG2 && debugflag2){
            console("MboxReceive: mailbox became inactive. \n");
         }
         if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){
            
            unblockProcess(BLOCKRECEIVE, mbox_id, NULL, 0);
         }
         else if (MailBoxTable[mbox_id].numWaitSendProc > 0){

            unblockProcess(BLOCKSEND, mbox_id, NULL, 0);
         }
         else{

            unblock_proc(BlockPid);
         }
         enableInterrupts();
         return -3;
      }

      enableInterrupts();
      return retVal;
   }

   // if no msg availabe then block receiver - add proc to waiting procs
   if (MailBoxTable[mbox_id].fullSlots == 0){

      blockProcess(BLOCKRECEIVE, mbox_id, msg_ptr, msg_size);

      // check if zapped after unblocked
      if (is_zapped()){
         //process was zapped
         if (DEBUG2 && debugflag2){
            console("MboxReceive: proc was zapped. \n");
         }
         enableInterrupts();
         return -3;
      }

      // check if mailbox is still available after unblock
      if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
         // mailbox became inactive
         if (DEBUG2 && debugflag2){
            console("MboxReceive: mailbox became inactive. \n");
         }
         if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){
            
            unblockProcess(BLOCKRECEIVE, mbox_id, NULL, 0);
         }
         else if (MailBoxTable[mbox_id].numWaitSendProc > 0){

            unblockProcess(BLOCKSEND, mbox_id, NULL, 0);
         }
         else{

            if (BlockPid != 0){
               unblock_proc(BlockPid);
            }
         }
         
         enableInterrupts();
         return -3;
      }
   }

   retVal = grabMsg(mbox_id, msg_ptr, msg_size);

   //now that there is open slot
   // need to unblock proc waiting to send 
   if (MailBoxTable[mbox_id].numWaitSendProc > 0){
      unblockProcess(BLOCKSEND, mbox_id, msg_ptr, msg_size);
   }
   
   // check if zapped after unblocked
   if (is_zapped()){
      //process was zapped
      if (DEBUG2 && debugflag2){
         console("MboxReceive: proc was zapped. \n");
      }
      enableInterrupts();
      return -3;
   }

   // check if mailbox is still available after unblock
   if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
      // mailbox became inactive
      if (DEBUG2 && debugflag2){
         console("MboxReceive: mailbox became inactive. \n");
      }
      enableInterrupts();
      return -3;
   }

   enableInterrupts();
   return retVal;

} /* MboxReceive */

/* ------------------------------------------------------------------------
   Name - MboxRelease
   Purpose - empties out a mailbox - if any processes are blocked on it- unblock
   Parameters - mailbox id
   Returns - -1 if not in use -3 if proc was zapped
   Side Effects - none
   ----------------------------------------------------------------------- */
/* returns 0 if successful, -1 if invalid arg */
int MboxRelease(int mbox_id){

   disableInterrupts();

   int retVal = 0;

   /*if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
      // mailbox is already inactive
      enableInterrupts();
      return -1;
   }*/

   // need to mark the mailbox as being released:
   MailBoxTable[mbox_id].status = MBSTATUS_INACTIVE;

   /*if (MailBoxTable[mbox_id].numWaitReceiveProc > 0 || MailBoxTable[mbox_id].numWaitSendProc > 0){
      int loop = MailBoxTable[mbox_id].numWaitReceiveProc;
      // check for blocked procs and unblock them
      for (int i = 0; i < loop; i++){
         //zap(MailBoxTable->waitingReceiveProc->pid);
         unblockProcess(BLOCKRECEIVE, mbox_id, NULL, 0);
      }
      loop = MailBoxTable[mbox_id].numWaitSendProc;
      for (int i = 0; i < loop; i++){
      
         //zap(MailBoxTable[mbox_id].waitingSendProc->pid);
         unblockProcess(BLOCKSEND, mbox_id, NULL, 0);
      }
      block_me(50);
   }*/

   // unblock any waiting procs
   if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){

      unblockProcess(BLOCKRECEIVE, mbox_id, NULL, 0);
   }
   
   // unblock any waiting procs
   if (MailBoxTable[mbox_id].numWaitSendProc > 0){

      unblockProcess(BLOCKSEND, mbox_id, NULL, 0);
   }
   // block the calling proc
   BlockPid = getpid() % MAXPROC;
   block_me(50);
   BlockPid = -1;

   // free all of the slots
   slot_ptr loopSlot = MailBoxTable[mbox_id].headSlotPtr;

   for (int i = 0; i < MailBoxTable[mbox_id].numSlots; i++){

      MailBoxTable[mbox_id].headSlotPtr = MailBoxTable[mbox_id].headSlotPtr->nextSlotPtr;
      free(loopSlot);
      loopSlot = MailBoxTable[mbox_id].headSlotPtr;
   }

   // need to reclaim mail slots allocated for the mbox so can be reused
   OpenMailSlots = OpenMailSlots + MailBoxTable[mbox_id].fullSlots;

   // clear out mailbox entry
   MailBoxTable[mbox_id].numSlots = 0;
   MailBoxTable[mbox_id].fullSlots = 0;
   MailBoxTable[mbox_id].slotSize = 0;
   MailBoxTable[mbox_id].numWaitSendProc = 0;
   MailBoxTable[mbox_id].numWaitReceiveProc = 0;
   MailBoxTable[mbox_id].waitingSendProc = NULL;
   MailBoxTable[mbox_id].waitingReceiveProc = NULL;
   MailBoxTable[mbox_id].headSlotPtr = NULL;
   MailBoxTable[mbox_id].openSlot = MailBoxTable[mbox_id].headSlotPtr;

   if (is_zapped()){
      retVal = -3;
   }

   enableInterrupts();
   return retVal;
}/*MboxRelease*/


/* ------------------------------------------------------------------------
   Name - MboxCondSend
   Purpose - sends msg to mailbox but does not block 
   Parameters - mailbox id, msg pointer, msg size
   Returns - -1 illegal args, -2 mailbox full, -3 if zapped
   Side Effects - none
   ----------------------------------------------------------------------- */
/* returns 0 if successful, 1 if mailbox full, -1 if illegal args */
int MboxCondSend(int mbox_id, void *msg_ptr, int msg_size){

   check_kernel_mode("MboxCondSend");

   /* Disable interrupts */
   disableInterrupts();

   // error checking for mbox_id
   if ((MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE) || mbox_id > 1999 || mbox_id < 0){
      // invalid mailbox id
      if (DEBUG2 && debugflag2){
         console("MboxCondSend: invalid mailbox id. \n");
      }
      enableInterrupts();
      return -1;
   }

   // error checking for msg_size
   if (msg_size > MailBoxTable[mbox_id].slotSize || msg_size > MAX_MESSAGE){
      // msg size invalid
      if (DEBUG2 && debugflag2){
         console("MboxCondSend: msg size invalid. \n");
      }
      enableInterrupts();
      return -1;
   }

   if (MailBoxTable[mbox_id].numSlots == 0){

      // check if another process is blocked to receive on this box
      if (MailBoxTable[mbox_id].numWaitReceiveProc == 0){
         // if nothing waiting - leave
         enableInterrupts();
         return -2;
      }
      else{
         // if somthing is waiting to receive - unblock it
         if (unblockProcess(BLOCKRECEIVE, mbox_id, msg_ptr, msg_size) == -1){
            if (DEBUG2 && debugflag2){
               console("MboxCondSend: size not right. \n");
            }
            enableInterrupts();
            return -1;
         } 
      }

      if (is_zapped()){
         //process was zapped
         if (DEBUG2 && debugflag2){
            console("MboxCondSend: proc was zapped. \n");
         }
         enableInterrupts();
         return -3;
      }

      if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
         // mailbox became inactive
         if (DEBUG2 && debugflag2){
            console("MboxReceive: mailbox became inactive. \n");
         }
         if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){
            
            unblockProcess(BLOCKRECEIVE, mbox_id, NULL, 0);
         }
         else if (MailBoxTable[mbox_id].numWaitSendProc > 0){

            unblockProcess(BLOCKSEND, mbox_id, NULL, 0);
         }
         else{

            if (BlockPid != 0){
               unblock_proc(BlockPid);
            }
         }
         
         enableInterrupts();
         return -3;
      }

      enableInterrupts();
      return 0;
   }

   // all slots full - so leave
   if (MailBoxTable[mbox_id].numSlots == MailBoxTable[mbox_id].fullSlots){

      enableInterrupts();
      return -2;
   }

   // all slots are used on system - so leave
   if (OpenMailSlots == 0){

      enableInterrupts();
      return -2;
   }

   // put the msg in the slot
   deliverMsg(mbox_id, msg_ptr, msg_size);


   // now that there is a msg in slot 
   // we can unblock any waiting procs
   if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){
      if (unblockProcess(BLOCKRECEIVE, mbox_id, msg_ptr, msg_size) == -1){
         if (DEBUG2 && debugflag2){
            console("MboxCondSend: size not right. \n");
         }
         enableInterrupts();
         return -1;
      } 
   }

   if (is_zapped()){
      //process was zapped
      if (DEBUG2 && debugflag2){
         console("MboxCondSend: proc was zapped. \n");
      }
      enableInterrupts();
      return -3;
   }

   if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
         // mailbox became inactive
         if (DEBUG2 && debugflag2){
            console("MboxReceive: mailbox became inactive. \n");
         }
         if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){
            
            unblockProcess(BLOCKRECEIVE, mbox_id, NULL, 0);
         }
         else if (MailBoxTable[mbox_id].numWaitSendProc > 0){

            unblockProcess(BLOCKSEND, mbox_id, NULL, 0);
         }
         else{

            if (BlockPid != 0){
               unblock_proc(BlockPid);
            }
         }
         
         enableInterrupts();
         return -3;
      }

   enableInterrupts();
   return 0;

}/*MboxCondSend*/


/* ------------------------------------------------------------------------
   Name - MboxCondReceive
   Purpose - grab a message from a mailbox but do not block
   Parameters - mailbox is, msg pointer, msg size
   Returns - returns 0 if successful, 1 if no msg available, -1 if illegal args
   Side Effects - none
   ----------------------------------------------------------------------- */
/* returns 0 if successful, 1 if no msg available, -1 if illegal args */
int MboxCondReceive(int mbox_id, void *msg_ptr, int msg_max_size){
   
   int retVal = 0;

   check_kernel_mode("MboxReceive");

   /* Disable interrupts */
   disableInterrupts();

   // error checking for mbox_id
   if ((MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE) || mbox_id > 1999 || mbox_id < 0){
      // invalid mailbox id
      if (DEBUG2 && debugflag2){
         console("MboxReceive: invalid mailbox id. \n");
      }
      enableInterrupts();
      return -1;
   }

   // error checking for msg_size
   if (msg_max_size > MAX_MESSAGE){
      // msg size invalid
      if (DEBUG2 && debugflag2){
         console("MboxReceive: msg size invalid. \n");
      }
      enableInterrupts();
      return -1;
   }

   // 0 slot mailbox
   if (MailBoxTable[mbox_id].numSlots == 0){

      // check if another process is blocked to send on this box
      if (MailBoxTable[mbox_id].numWaitSendProc == 0){
         // if nothing waiting - leave

         enableInterrupts();
         return -2;
      }
      else{
         // if somthing is waiting to send - unblock it
         retVal = unblockProcess(BLOCKSEND, mbox_id, msg_ptr, msg_max_size);
            
      }

      if (is_zapped()){
         //process was zapped
         if (DEBUG2 && debugflag2){
            console("MboxReceive: proc was zapped. \n");
         }
         enableInterrupts();
         return -3;
      }

      if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
         // mailbox became inactive
         if (DEBUG2 && debugflag2){
            console("MboxReceive: mailbox became inactive. \n");
         }
         if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){
            
            unblockProcess(BLOCKRECEIVE, mbox_id, NULL, 0);
         }
         else if (MailBoxTable[mbox_id].numWaitSendProc > 0){

            unblockProcess(BLOCKSEND, mbox_id, NULL, 0);
         }
         else{

            if (BlockPid != 0){
               unblock_proc(BlockPid);
            }
         }
         
         enableInterrupts();
         return -3;
      }

      enableInterrupts();
      return retVal;
   }

   // if no msg availabe then leave
   if (MailBoxTable[mbox_id].fullSlots == 0){

      enableInterrupts();
      return -2;
   }

   // grab the msg from slot
   retVal = grabMsg(mbox_id, msg_ptr, msg_max_size);

   //now that there is open slot
   // need to unblock proc waiting to send 
   if (MailBoxTable[mbox_id].numWaitSendProc > 0){
      unblockProcess(BLOCKSEND, mbox_id, msg_ptr, msg_max_size);
   }
   
   // check if zapped after unblocked
   if (is_zapped()){
      //process was zapped
      if (DEBUG2 && debugflag2){
         console("MboxReceive: proc was zapped. \n");
      }
      enableInterrupts();
      return -3;
   }

   // check if mailbox is still available after unblock
   if (MailBoxTable[mbox_id].status == MBSTATUS_INACTIVE){
         // mailbox became inactive
         if (DEBUG2 && debugflag2){
            console("MboxReceive: mailbox became inactive. \n");
         }
         if (MailBoxTable[mbox_id].numWaitReceiveProc > 0){
            
            unblockProcess(BLOCKRECEIVE, mbox_id, NULL, 0);
         }
         else if (MailBoxTable[mbox_id].numWaitSendProc > 0){

            unblockProcess(BLOCKSEND, mbox_id, NULL, 0);
         }
         else{

            if (BlockPid != 0){
               unblock_proc(BlockPid);
            }
         }
         
         enableInterrupts();
         return -3;
      }

   enableInterrupts();
   return retVal;


}/*MboxCondReceive*/

int check_io(){

   if (DeviceCounter > 0){
      return 1;
   }

   return 0; 
}

static void disableInterrupts(void){
   /* turn the interrupts OFF if we are in kernel mode */
   if((PSR_CURRENT_MODE & psr_get()) == 0) {
      //not in kernel mode
      console("Kernel mode expected, but function called in user mode.\n");
      halt(1);
   } else
      /* We ARE in kernel mode */
      psr_set( psr_get() & ~PSR_CURRENT_INT );
} /* disableInterrupts */

static void enableInterrupts(void){
   /* turn the interrupts off if we are in kernel mode */
   if((PSR_CURRENT_MODE & psr_get()) == 0) {
      //not in kernel mode
      console("Kernel mode expected, but function called in user mode.\n");
     halt(1);
   } else
      /* We ARE in kernel mode */
      psr_set( psr_get() | PSR_CURRENT_INT );
}

static void check_kernel_mode(char procName[MAXNAME]) {
   if (PSR_CURRENT_MODE & psr_get() == 0) {
      console("kernel function called while in user mode, by process with name %s Halting...\n", procName);
      halt(1);
   }
}

static int GetNextEmptyMailbox(){

   int nextPosition = nextMailboxId % MAXMBOX;
   int numFull = 0;

   // loop to find next empty mail box if any
   while ((numFull < MAXMBOX) && MailBoxTable[nextPosition].status != MBSTATUS_INACTIVE){
      nextMailboxId++;
      nextPosition = nextMailboxId % MAXMBOX;
      ++numFull;
   }

   // nextposition contains next empty location in MailBoxTable 
   if (numFull < MAXMBOX){
      
      return nextPosition;
   }

   // all mail boxes full
   else{
      
      if (DEBUG2 && debugflag2){
         console("GetNextEmptyMailbox: All mailboxes are full. \n");
      }
      return -1;
   }

}/*GetNextEmptyMailbox*/

void blockProcess(int blockStatus, int mbox_id, void *msg_ptr, int msg_size){

   // allocate space for new proc
   mbox_proc_ptr process = (mbox_proc_ptr)malloc(sizeof(struct mbox_proc));
   mbox_proc_ptr loopProc;

   // innitialize the new proc
   process->pid = (getpid() % MAXPROC);
   memcpy(process->msg, msg_ptr, msg_size);
   process->MBoxId = mbox_id;
   process->nextWaitProc = NULL;

   //add to the send waiting list
   if (blockStatus == BLOCKSEND){
      // if this is the only one waiting
      if (MailBoxTable[mbox_id].numWaitSendProc == 0){

         MailBoxTable[mbox_id].numWaitSendProc += 1;
         MailBoxTable[mbox_id].waitingSendProc = process;
      }
      else{
         // add to the end of list
         MailBoxTable[mbox_id].numWaitSendProc += 1;
         loopProc = MailBoxTable[mbox_id].waitingSendProc;

         while(loopProc->nextWaitProc != NULL){

            loopProc = loopProc->nextWaitProc;
         }
         loopProc->nextWaitProc = process;
      }
      
   }
   // add to the receive waiting list
   if (blockStatus == BLOCKRECEIVE){
      // if this is the first in line
      if (MailBoxTable[mbox_id].numWaitReceiveProc == 0){

         MailBoxTable[mbox_id].numWaitReceiveProc += 1;
         MailBoxTable[mbox_id].waitingReceiveProc = process;
      }
      else{
         // put at end 
         MailBoxTable[mbox_id].numWaitReceiveProc += 1;
         loopProc = MailBoxTable[mbox_id].waitingReceiveProc;

         while(loopProc->nextWaitProc != NULL){

            loopProc = loopProc->nextWaitProc;
         }
         loopProc->nextWaitProc = process;
      }
   }

   // actually block
   block_me(blockStatus);

   // now that process is unblocked we need to move the msg from receive->msg to msg_ptr
   if (MailBoxTable[mbox_id].numSlots == 0 && blockStatus == BLOCKRECEIVE){
      memcpy(msg_ptr, MailBoxTable[mbox_id].waitingReceiveProc->msg, msg_size);
   }

   // now that we're done with the waiting proc 
   // clear it out
   if (blockStatus == BLOCKRECEIVE){

      MailBoxTable[mbox_id].numWaitReceiveProc--;

      if (MailBoxTable[mbox_id].numWaitReceiveProc == 0){

         free(MailBoxTable[mbox_id].waitingReceiveProc);
      }
      else{
            
         mbox_proc_ptr temp = MailBoxTable[mbox_id].waitingReceiveProc;

         MailBoxTable[mbox_id].waitingReceiveProc = MailBoxTable[mbox_id].waitingReceiveProc->nextWaitProc;

         free(temp);
      }
   }

}/*blockProcess*/

int unblockProcess(int blockStatus, int mbox_id, void *msg_ptr, int msg_size){

   int pid, retVal = 0;

   // copy the msg to the proper place
   if (MailBoxTable[mbox_id].numSlots == 0){
      if (blockStatus == BLOCKRECEIVE){

         memcpy(MailBoxTable[mbox_id].waitingReceiveProc->msg, msg_ptr, msg_size);
      }

      if (blockStatus == BLOCKSEND){

         memcpy(msg_ptr, MailBoxTable[mbox_id].waitingSendProc->msg, msg_size);

      }
   }

   if (blockStatus == BLOCKRECEIVE){

      pid = MailBoxTable[mbox_id].waitingReceiveProc->pid;
   }
   if (blockStatus == BLOCKSEND){

      // will not need send waiting list agaion so we can clear it out here
      pid = MailBoxTable[mbox_id].waitingSendProc->pid;

      MailBoxTable[mbox_id].numWaitSendProc--;

      if (MailBoxTable[mbox_id].waitingSendProc == 0){

         free(MailBoxTable[mbox_id].waitingSendProc);
      }
      else{

         mbox_proc_ptr temp = MailBoxTable[mbox_id].waitingSendProc;
            
         MailBoxTable[mbox_id].waitingSendProc = MailBoxTable[mbox_id].waitingSendProc->nextWaitProc;

         free(temp);
      }
   }

   unblock_proc(pid);
   return retVal;

}/*unblockProcess*/


void deliverMsg(int mbox_id, void *msg_ptr, int msg_size){

   // no slots are available on system
   if (OpenMailSlots == 0){
      console("deliverMsg: All slots are used. \n");
      halt(1);
   }

   slot_ptr buffer = MailBoxTable[mbox_id].openSlot;
   // copy msg to open slot
   memcpy(buffer->msg, msg_ptr, msg_size);
   // update the slot info
   MailBoxTable[mbox_id].openSlot->status = SLOTSTATUS_FULL;

   MailBoxTable[mbox_id].openSlot->realSize = msg_size; 

   MailBoxTable[mbox_id].fullSlots++;

   // update the openslot pointer
   if (MailBoxTable[mbox_id].fullSlots != MailBoxTable[mbox_id].numSlots){

      MailBoxTable[mbox_id].openSlot = MailBoxTable[mbox_id].openSlot->nextSlotPtr;
   }

   OpenMailSlots--;

}/*deliverMsg*/


int grabMsg(int mbox_id, void *msg_ptr, int msg_size){

   // if msg available in mbox use memcpy from slot to buffer
   memcpy(msg_ptr, MailBoxTable[mbox_id].headSlotPtr->msg, msg_size);

   // return the realsize
   int retVal = MailBoxTable[mbox_id].headSlotPtr->realSize;
   // update slot info
   MailBoxTable[mbox_id].headSlotPtr->status = SLOTSTATUS_EMPTY;

   slot_ptr loopSlot = MailBoxTable[mbox_id].headSlotPtr;
   //loop to get to end of slots
   for (int i = 1; i < MailBoxTable[mbox_id].numSlots; i++){

      loopSlot = loopSlot->nextSlotPtr;
   }
   
   // add the now empty slot to end of list
   loopSlot->nextSlotPtr = MailBoxTable[mbox_id].headSlotPtr;

   if (MailBoxTable[mbox_id].fullSlots == MailBoxTable[mbox_id].numSlots){
      // update the open slot pointer
      MailBoxTable[mbox_id].openSlot = loopSlot->nextSlotPtr;
   }

   MailBoxTable[mbox_id].fullSlots--;

   // make the next slot in list the head node
   MailBoxTable[mbox_id].headSlotPtr = MailBoxTable[mbox_id].headSlotPtr->nextSlotPtr;

   loopSlot = loopSlot->nextSlotPtr;

   loopSlot->nextSlotPtr = NULL; 

   // one more slot avail on system
   OpenMailSlots++;

   return retVal;

}/*grabMsg*/


static void nullsys(sysargs *arg){

   console("nullsys(): Invalid syscall %d. Halting...\n", arg->number);
   halt(1);

}/*invalidSys*/


static void clockInterrupt(int dev, void *arg){

   int intUnit = (int) arg;

   // if over time
   if (read_cur_start_time() >= 100000){

      time_slice();
   }
   // inc clock counter
   ClockCounter++;

   int inputResult, inputReturn;
   inputReturn = device_input(dev, intUnit, &inputResult);

   if (inputReturn != DEV_OK){

      halt(1);
   }

   // every fifth time
   if (ClockCounter % 5 == 0){

      MboxCondSend(ClockMail.mbox_id, &inputResult, sizeof(inputResult));
   }

}/*clockInterrupt*/


static void diskInterrupt(int dev, void *arg){

   int unit = (int)arg;

   // error checking
   if (dev != DISK_DEV || unit > DISK_UNITS || unit < 0){
      // bad args
      halt(1);
   }

   // mailbox was released
   if (DiskMail[unit].status == MBSTATUS_INACTIVE){

      halt(1);
   }

   int status, inputReturn;
   inputReturn = device_input(DISK_DEV, unit, &status);

   MboxCondSend(DiskMail[unit].mbox_id, &status, sizeof(status));

   if (inputReturn != DEV_OK){

      halt(1);
   }

}/*diskInterrupt*/


static void terminalInterrupt(int dev, void *arg){

   int intUnit = (int) arg;

   // error checking
   if (dev != TERM_DEV || intUnit > TERM_UNITS || intUnit < 0){
      //bad args
      halt(1);
   }

   // mailbox was released
   if (TerminalMail[intUnit].status == MBSTATUS_INACTIVE){

      halt(1);
   }

   int inputResult, inputReturn;
   inputReturn = device_input(TERM_DEV, intUnit, &inputResult);

   MboxCondSend(TerminalMail[intUnit].mbox_id, &inputResult, sizeof(inputResult));

   if (inputReturn != DEV_OK){

      halt(1);
   }

}/*terminalInterrupt*/


static void systemcallInterrupt(int dev, void *arg){
   sysargs *sysCallStruct = (sysargs *) arg;

   //error checking
   if (dev != SYSCALL_INT){
      halt(1);
   }

   if (sysCallStruct->number >= MAXSYSCALLS || sysCallStruct->number < 0){
      console("syscall_handler(): sys number %d is wrong.  Halting...\n", sysCallStruct->number);
      halt(1);
   }

   psr_set(psr_get() | PSR_CURRENT_INT);
   sys_vec[sysCallStruct->number](sysCallStruct);

}/*systemcallInterrupt*/


int waitdevice(int type, int unit, int *status){
   mail_box typeMail;

   // which mailbox to use
   // depends on the device
   if (type == CLOCK_DEV){

      typeMail = ClockMail;
   }
   else if (DISK_INT){

      typeMail = DiskMail[unit];
   }
   else if (TERM_INT){

      typeMail = TerminalMail[unit];
   }
   else{
      console("waitDevice(): bad type");
      halt(1);
   }

   DeviceCounter++; 

   // FIXME need to use MboxReceive, but using MboxReceive will cause 
   // process to be blocked waiting for msg. msg never seems arrives? 
   // so process will never be unblocked. why?
   // using MboxCondReceive works, because it doesn't block, but it is incorrect
   MboxCondReceive(typeMail.mbox_id, status, sizeof(int)); 
   //MboxReceive(typeMail.mbox_id, status, sizeof(int)); 

   DeviceCounter--;

   if (is_zapped()){
      return -1;
   }

   return 0;

}/*waitdevice*/