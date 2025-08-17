#ifndef LOCATION_H
#define LOCATION_H

#include "ItemList.h"

#define MAX_LOC_NAME_STRING 25
#define MAX_LOC_DESCRIPTION_STRING 250

typedef struct{
    char name[MAX_LOC_NAME_STRING];
    char description[MAX_LOC_DESCRIPTION_STRING];
    int north;                                      // index of location to the north
    int east;                                       // index of location to the east
    int south;                                      // index of location to the south
    int west;                                       // index of location to the west
    ItemList items;                                 // items in this location
} Location;

/*
Returns the number of map locations loaded into the map array or returns -1 
if there's an error loading the locations. If an error is returned, 
the program should terminate.
*/
int LocationReadMap(Location map[], int maxLocations, char *filename);

/*
Adds the item specified by itemNumber to the item list for the location specified by pLocation.
*/
void LocationAddItem(Location *pLocation, int itemNumber);

/*
Removes the item specified by itemNumber from the item list for the location specified by pLocation.
*/
void LocationRemoveItem(Location *pLocation, int itemNumber);

/*
Returns true if the itemNumber is contained within the 
item list for the location specified by pLocation and returns false if it is not.
*/
bool LocationHasItem(Location *pLocation, int itemNumber);


#endif