/* films3.c -- using an ADT-style linked list */
 /* compile with list.c                       */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#include "list.h"  /* defines List, Item */

void showmovies(ItemData item);
char * s_gets(char * st, int n); 

int main(void)
{
    List movies; 
    ItemData temp;

    /* initialize */ 
    InitializeList(&movies); 
    if (ListIsFull(&movies)) 
    {
        fprintf(stderr,"No memory available! Bye!\n");
        exit(1); 
    }

    /* gather and store */
    puts("Enter the first movie title:");
    while (s_gets(temp.title, TSIZE) != NULL && temp.title[0] != '\0') 
    {
        temp.stars = -1;

        while ((temp.stars < 0) || (temp.stars > 5))
        {
            puts("Enter your rating in number of stars <1-5>:"); 
            scanf("%d", &temp.stars); 
            while(getchar() != '\n')
               continue;
        }
        if (AddItem(temp, &movies)==false) 
        {
            fprintf(stderr,"Problem allocating memory\n");
            break; 
        }
        if (ListIsFull(&movies)) 
        {
            puts("The list is now full.");
            break; 
        }
        puts("Enter the next movie title (use an empty line to stop):"); 
    }

    /* display */
    if (ListIsEmpty(&movies))
        printf("No data entered. "); 
    else
    {
        printf ("Here is the movie list:\n"); 
        Traverse(&movies, showmovies);
    }
    printf("You entered %d movies.\n", ListItemCount(&movies));
    /* clean up */ 
    EmptyTheList(&movies); 
    printf("Bye!\n");
    return 0; 
}

void showmovies(ItemData item) 
{
    printf("Movie: %-30s rating: ", item.title);
    for (int i = 0; i < item.stars; ++i) printf("*");
    for (int i = item.stars; i < 5; ++i) printf("-");
    printf("\n");    
}

char * s_gets(char * st, int n)
{
    char * ret_val; 
    char * find;
    ret_val = fgets(st, n, stdin); 
    if (ret_val)
    {
        find = strchr(st, '\n');  //look for newline
        if (find)                 //if the address is not NULL,
            *find = '\0';         // place a null character there
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val; 
}