#include <stdio.h>

#include "Game.h"

int main()
{
   Game game;

   GameInitialize(&game);

   for(int i=0; i<game.itemCount; i++)
   {
      printf("ITEM %d %s %s\n", i, game.items[i].name, game.items[i].description);
   }

   for(int i=0; i<game.numLocations; i++)
   {
      printf("LOC %d %s %s <%d %d %d %d>\n",
        i,
        game.map[i].name,
        game.map[i].description,
        game.map[i].north,
        game.map[i].east,
        game.map[i].south,
        game.map[i].west
        );
   }

   for(int i=0; i<game.numLocations; i++)
   {
      if(game.map[i].items.count > 0 )
      {
         printf("LOC %d contains ", i);
         for(int j=0; j<game.map[i].items.count; j++)
         {
            printf(" %d", game.map[i].items.items[j]);
         }
         printf("\n");
      }
   }
}