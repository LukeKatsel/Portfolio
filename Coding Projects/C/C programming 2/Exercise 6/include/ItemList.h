#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <stdbool.h>

#include "Item.h"

#define MAX_ITEM_LIST 6

typedef struct{
    int items[MAX_ITEM_LIST];   // the itemNumbers in the list
    int count;                  // the number of items in the list
} ItemList;

/*Initializes the ItemList structure pointed to by pItemList as an 
empty list.
*/
void ItemListInit(ItemList *pItemList);

/*
Adds item identified by itemNumber to the end of the list. 
Have the function return the current count of items in the list.
*/
int ItemListAddItem(ItemList *pItemList, int itemNumber);

/*
Removes item identified by itemNumber from the list. 
Have the function return the current number of items in the list.
*/
int ItemListRemoveItem(ItemList *pItemList, int itemNumber);

/*
Determines if the list pointed to by pItemList contains the item identified by itemNumber.
*/
bool ItemListHasItem(ItemList *pItemList, int itemNumber);


#endif