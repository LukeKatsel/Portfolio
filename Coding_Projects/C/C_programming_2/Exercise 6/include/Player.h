#ifndef PLAYER_H
#define PLAYER_H

#include "Location.h"

typedef struct{
    int location;
    ItemList items;
} Player;

/*
Initializes the Player structure pointed to by pPlayer. 
Sets the initial location number to the value specified by locationNumber.
*/
void PlayerInit(Player *pPlayer, int locationNumber);

/*
Adds the item specified by itemNumber to the item list for the player specified by pPlayer.
*/
void PlayerAddItem(Player *pPlayer, int itemNumber);

/*
Removes the item specified by itemNumber from the item list for the player specified by pPlayer.
*/
void PlayerRemoveItem(Player *pPlayer, int itemNumber);

/*
Returns true if the itemNumber is contained within the item list for the player 
specified by pPlayer and returns false if it is not.
*/
bool PlayerHasItem(Player *pPlayer, int itemNumber);

#endif