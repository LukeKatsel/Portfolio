#ifndef GAME_H
#define GAME_H

#include "Player.h"

#define MAX_MAP_LOCATIONS 50
#define MAX_ITEM_COUNT 50

typedef struct {
    int numLocations;
    Location map[MAX_MAP_LOCATIONS];
    int itemCount;
    Item items[MAX_ITEM_COUNT];
    Player player;
} Game;

/*
Initializes the game structure and calls the initialize
 routines for the game’s map and the game’s items. 
 The player object is also initialized.
*/
int GameInitialize(Game *pGame);

#endif