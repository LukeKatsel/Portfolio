#include <stdio.h>

#include "Item.h"

int main()
{
    int place;
    int numItems = 0;
    Item items[MAX_ITEMS];
    char *invalidItem = "invalid";

    /* load the items from the data file. */
    if( (numItems = ItemReadItems(items, MAX_ITEMS, "items.txt")) > 0 )
    {
        /* Display the items and their index in the array. */
        for(int i=0; i<numItems; i++)
        {
            printf("%d\t\"%s\"\t\"%s\"\n", i, items[i].name, 
                                                  items[i].description);
        }

        /* Test the find item function. */
        for(int i=0; i<numItems; i++)
        {
            if( (place = ItemGetItemNumber(items, numItems, items[i].name)) > -1)
            {
                printf("The item number for %s is %d\n", items[i].name, place);
            }
            else
            {
                printf("Test Failed: Can't find %s\n", items[i].name);
            }
        }

        /* test the function with an item that should not be found */
        if( (place = ItemGetItemNumber(items, numItems, invalidItem)) > -1)
        {
            printf("Test Failed: The item %s was found.\n", invalidItem);
        }
        else
        {
            printf("Item not found in the list of items.\n");
        }
    }
    else
    {
        printf("ERROR: Unable to load items\n");
    }
}
