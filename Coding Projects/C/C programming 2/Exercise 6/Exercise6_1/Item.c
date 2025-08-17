#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Item.h"

/*
Loads the list of items from a text file with comma delimited fields.
 Returns the number of objects loaded from the filename 
 (or -1 if unable to open the file and load the data). 
 Fills the Item array items with the contents of a file entitled
  "items.txt".
*/
int ItemReadItems(Item items[], int maxItems, char *filename){
  int i = 0, strMax = MAX_ITEM_NAME_STRING + MAX_ITEM_DESCRIPTION_STRING;
  char str[strMax];
  FILE *file;
  char *tok;
  char *tok2;

  

  if ((file = fopen(filename, "r")) == NULL){       //open file with error checking
    printf("Unable to open file: %s\n", filename);
    return -1;                                      // return -1 if can't open
  }

  else{
    while (fgets(str, strMax, file) != EOF){
      tok = strtok(str, "\"");
      tok2 = strtok(NULL, "\"");
      tok2 = strtok(NULL, "\"");
      memcpy(items[i].name, tok, MAX_ITEM_NAME_STRING);   // use strtok to jump through file
      memcpy(items[i].description, tok2, MAX_ITEM_DESCRIPTION_STRING);
      i++;
    }
    fclose(file);
    return i;
  }
}

/*
Finds an item by itemName and returns the item number of the item 
itemName. The function returns -1 if an item with the specified 
itemName is not present. The item number is index of the item in the
items array.
*/
int ItemGetItemNumber(Item items[], int maxItems, char *itemName){
  int i;

  for (i = 0; i < maxItems; i ++){
    if ((strncmp(itemName, items[i].name, MAX_ITEM_NAME_STRING)) ==  0 ){
      return i;
    }
  }
  return -1;
}
