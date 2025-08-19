#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ItemList.h"

/*
Initializes the ItemList structure pointed to by pItemList as an 
empty list.
*/
void ItemListInit(ItemList *pItemList){
    int i;

    for(i = 0; i < MAX_ITEM_LIST; i++){
        pItemList->items[i] = 0;            // set everything to 0
    }
    pItemList->count = 0;
}

/*
Adds item identified by itemNumber to the end of the list. 
Have the function return the current count of items in the list.
*/
int ItemListAddItem(ItemList *pItemList, int itemNumber){                                                             

    pItemList->items[pItemList->count] = itemNumber;        //add item at end which is count index
    pItemList->count++;

    return pItemList->count;
}

/*
Removes item identified by itemNumber from the list. 
Have the function return the current number of items in the list.
*/
int ItemListRemoveItem(ItemList *pItemList, int itemNumber){
    int i;
    int itemLoc = -1;

    for (i = 0; i < MAX_ITEM_LIST; i++){
        if (pItemList->items[i] == itemNumber){
            itemLoc = i;
            break;
        }
    }

    if (itemLoc != -1){
        for (i = itemLoc; i < (pItemList->count - 1); i++){
            pItemList->items[i] = pItemList->items[i + 1];          // shift items
        }
        pItemList->items[pItemList->count] = 0;
        pItemList->count = pItemList->count - 1;                    // decrement count
    }

    return pItemList->count;
}

/*
Determines if the list pointed to by pItemList contains the item identified by itemNumber.
*/
bool ItemListHasItem(ItemList *pItemList, int itemNumber){
    int i;

    for (i = 0; i < pItemList->count; i++){
        if (pItemList->items[i] == itemNumber){
            return 1;
            break;
        }
    }
    return 0;
}
