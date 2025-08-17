#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Location.h"
#include "Item.h"

/*
Returns the number of map locations loaded into the map array or returns -1 
if there's an error loading the locations. If an error is returned, 
the program should terminate.
*/
int LocationReadMap(Location map[], int maxLocations, char *filename){
    int i = 0, strMax = 300;
    char str[strMax];
    FILE *file;
    char *tok;

    if ((file = fopen(filename, "r")) == NULL){
        printf("Unable to open file: %s\n", filename);
        return -1;
    }

    else{
        while (fgets(str, strMax, file) != EOF){
            tok = strtok(str, ",");
            map[i].north = atoi(tok);                   // lots of strtok
            tok = strtok(NULL, ",");
            map[i].east = atoi(tok);                    // use atoi() for numbers
            tok = strtok(NULL, ",");
            map[i].south = atoi(tok);
            tok = strtok(NULL, ",");
            map[i].west = atoi(tok);
            tok = strtok(NULL, "\"");
            tok = strtok(NULL, "\"");
            memcpy(map[i].name, tok, MAX_LOC_NAME_STRING);
            tok = strtok(NULL, "\"");
            tok = strtok(NULL, "\"");
            memcpy(map[i].description, tok, MAX_LOC_DESCRIPTION_STRING);
            i++;
            
        }
    }
    fclose(file);
    return i;
    
}



/*
Adds the item specified by itemNumber to the item list for the location specified by pLocation.
*/
void LocationAddItem(Location *pLocation, int itemNumber){
    ItemListAddItem(&pLocation->items, itemNumber);
}

/*
Removes the item specified by itemNumber from the item list for the location specified by pLocation.
*/
void LocationRemoveItem(Location *pLocation, int itemNumber){
    ItemListRemoveItem(&pLocation->items, itemNumber);
}

/*
Returns true if the itemNumber is contained within the 
item list for the location specified by pLocation and returns false if it is not.
*/
bool LocationHasItem(Location *pLocation, int itemNumber){
    return ItemListHasItem(&pLocation->items, itemNumber);
}
