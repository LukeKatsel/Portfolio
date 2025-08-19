#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Location.h"
#include "Player.h"

#define MAX_LOCATIONS   25
#define TEST_ITEM_COUNT 10

int main()
{
    int numLocations = 0;
    Location map[MAX_LOCATIONS];
    Player player;
    int i;
    
    srand(clock());

    if( (numLocations = LocationReadMap(map, MAX_LOCATIONS, "map.txt")) > 0 )
    {
        for(int i=0; i<numLocations; i++)
        {
            printf("%d\t\"%s\"\t\"%s\" <%d, %d, %d, %d>\n",
                i,
                map[i].name,
                map[i].description,
                map[i].north,
                map[i].east,
                map[i].south,
                map[i].west
                );

            for (int j = 0; j < TEST_ITEM_COUNT; ++j)
            {
                // add a pretend item j
                LocationAddItem(&map[i], j);
            }    
        }

        // we should find each of these items in the locations
        for(i=0; i<numLocations; i++)
        {            
            // find a random item that is in the correct range
            int itemToFind = rand() % TEST_ITEM_COUNT;

            if (LocationHasItem(&map[i], itemToFind) == 0)
            {
                printf("TEST FAILED: item %d could not be found in location %d\n", itemToFind, i);
                break;
            }
        }

        if (i == numLocations)
        {
            // look for an item that we know does not exist
            for(i=0; i<numLocations; i++)
            {
                // make sure we are looking for something that is not there
                int itemToFind = (rand() % 4) + TEST_ITEM_COUNT;

                if (LocationHasItem(&map[i], itemToFind) == 0)
                {
//                    printf("item %d could not be found in location %d\n", itemToFind, i);
                }
                else
                {
                    printf("TEST FAILED: item %d incorrectly found in location %d\n", itemToFind, i);
                    break;
                }            
            }

            if (i == numLocations)
            {
                // remove the item and make sure it is not there
                for(i=0; i<numLocations; i++)
                {
                    int itemToRemove = rand() % TEST_ITEM_COUNT;

                    LocationRemoveItem(&map[i], itemToRemove);
                    
                    if (LocationHasItem(&map[i], itemToRemove) == 0)
                    {
//                        printf("item %d could not be found in location %d\n", itemToRemove, i);
                    }
                    else
                    {
                        printf("TEST FAILED: item %d incorrectly found in location %d\n", itemToRemove, i);
                    }           
                }

                if (i == numLocations)
                {
                    printf("LOCATIONS TEST PASSED\n");
                }
            }
        }
    }
    else
    {
        printf("ERROR: Unable to load map\n");
    }


    PlayerInit(&player, 0);
    PlayerAddItem(&player, 3);
    if (PlayerHasItem(&player, 3) == false)
    {
        printf("TEST FAILED: Player should have item.\n");
    }
    else
    {
        if (PlayerHasItem(&player, 54))
        {
            printf("TEST FAILED: Player should not have item.\n");
        }
        else
        {
            printf("PLAYER TEST PASSED\n");
        }
    }

}