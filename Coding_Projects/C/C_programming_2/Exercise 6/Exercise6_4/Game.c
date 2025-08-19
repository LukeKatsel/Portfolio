#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"

/*
Initializes the game structure and calls the initialize
routines for the game’s map and the game’s items. 
The player object is also initialized.
*/
int GameInitialize(Game *pGame){
    int i;

    pGame->numLocations = LocationReadMap(pGame->map, MAX_MAP_LOCATIONS, "map.txt");       // get location count and initialize locations
    pGame->itemCount = ItemReadItems(pGame->items, MAX_ITEM_COUNT, "items.txt");            // get item count and initialize items
   
    for (i = 0; i < pGame->itemCount; i++){
       LocationAddItem(&pGame->map[i], i);                                                  // add items to locations
    }

    PlayerInit(&pGame->player, 0);                                                          // initilize players

    return 0;   
}