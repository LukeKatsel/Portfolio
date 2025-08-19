#define DEBUG2 1

typedef struct mailslot *slot_ptr;
typedef struct mailslot mail_slot;
typedef struct mailbox mail_box;
typedef struct mbox_proc *mbox_proc_ptr;

struct mailbox {
   int            mbox_id;
   int            status;
   int            numSlots;
   int            fullSlots;
   int            slotSize;
   int            numWaitSendProc;
   int            numWaitReceiveProc;
   mbox_proc_ptr  waitingSendProc;
   mbox_proc_ptr  waitingReceiveProc;
   slot_ptr       headSlotPtr; 
   slot_ptr       openSlot;
   /* other items as needed... */
   // if changed = change start1 initialization
};

struct mailslot {
   int            mbox_id;
   int            status;
   int            realSize;
   char           msg[MAX_MESSAGE];
   slot_ptr       nextSlotPtr;
   /* other items as needed... */
   // if changed = change start1 initialization
};

struct mbox_proc {
   int            pid;
   char           msg[MAX_MESSAGE];
   int            MBoxId;
   mbox_proc_ptr  nextWaitProc;
};

struct psr_bits {
   unsigned int cur_mode:1;
   unsigned int cur_int_enable:1;
   unsigned int prev_mode:1;
   unsigned int prev_int_enable:1;
   unsigned int unused:28;
};

union psr_values {
   struct psr_bits bits;
   unsigned int integer_part;
};

#define MBSTATUS_INACTIVE 0
#define MBSTATUS_ACTIVE 1

#define SLOTSTATUS_EMPTY 0
#define SLOTSTATUS_FULL 1

#define NOTBLOCKED 0
#define BLOCKSEND 20
#define BLOCKRECEIVE 30
