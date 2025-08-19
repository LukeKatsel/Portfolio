/* list.c -- functions supporting list operations */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
 
/* local function prototype */
static void CopyToNode(ItemData item, ListNode * pnode);

/* interface functions */
/* set the list to empty */
void InitializeList(List * plist)
{
    plist->pListHead = NULL;
    plist->pListTail = NULL;
}
 
/* returns true if list is empty */
bool ListIsEmpty(const List * plist)
{
    if (plist->pListHead == NULL)               // if head node is empty then list is empty 
        return true;
    else
        return false;
}

/* returns true if list is full */
bool ListIsFull(const List * plist)
{
    ListNode * pt;
    bool full;

    pt = (ListNode *)malloc(sizeof(ListNode));
    if (pt == NULL)
        full = true;
    else
        full = false;
    free(pt);

    return full;
}

/* returns number of nodes */
unsigned int ListItemCount(const List * plist)
{
    unsigned int count = 0;
    ListNode * pnode = plist->pListHead;      

    while (pnode != NULL)
    {
        ++count;
        pnode = pnode->pNext;  /* set to next node */
    }

    return count;
}

/* creates node to hold item and adds it to the end of */
/* the list pointed to by plist (slow implementation) */
bool AddItem(ItemData item, List * plist)
{
    ListNode * pnew;
    ListNode *scan = plist->pListHead;

    pnew = (ListNode *)malloc(sizeof(ListNode));
    if (pnew == NULL)
        return false;     /* quit function on failure */

    CopyToNode(item, pnew);
    pnew->pNext = NULL;
    if (plist->pListHead == NULL){         /* empty list, so place */       
        plist->pListHead = pnew;         /* pnew at head of list */     
        plist->pListTail = pnew;         // if list is empty then set the head node and tail node to new node
    }
    else
    {
        while (scan->pNext != NULL)                 
            scan = scan->pNext;  // find end of list 
        scan->pNext = pnew;      // add pnew to end 
        plist->pListTail = pnew;          // set tail node to new node 
        
    }

    return true;
}

/* visit each node and execute function pointed to by pfun */
void Traverse(const List * plist, void(*pfun)(ItemData item))
{
    ListNode * pnode = plist->pListHead;    /* set to start of list */      

    while (pnode != NULL)
    {
        (*pfun)(pnode->itemData); /* apply function to item */
        pnode = pnode->pNext;  /* advance to next item */
    }
}

/* free memory allocated by malloc() */
/* set list pointer to NULL */
void EmptyTheList(List * plist)
{
    ListNode * psave;

    while (plist->pListHead != NULL)
    {
        psave = plist->pListHead->pNext; /* save address of next node */
        free(plist->pListHead);           /* free current node */      
        plist->pListHead = psave;         /* advance to next node */
    }
}

/* local function definition */
/* copies an item into a node */
static void CopyToNode(ItemData item, ListNode * pnode)
{
    pnode->itemData = item;  /* structure copy */
}