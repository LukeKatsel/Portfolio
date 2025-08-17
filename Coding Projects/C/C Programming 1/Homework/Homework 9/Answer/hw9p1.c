#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//Author: Luke Katsel
//Date created: 11/0/2021
//Brief description of the program: interactive program that reads data off of a file and lets a user search through with multiple criteria
//input(s): a data file and user inputs
//output(s): songs that fit filter criteria


/*note - this program works as far as I can tell, but it has some serious data allocation issues that
I do not understand or know how to fix. These problems cause the program to die shortly after running,
this has made it hard to debug*/


#define SSIZE 100
typedef struct song_s { 
    char name[SSIZE]; //song name 
    char artist[SSIZE]; //artist(s) 
    int year; //year released 
    int us_rank; //highest rank in US in that year 
}song;


void swap(int* x, int* y);
void selection_sort(int x[], int size);
void Load_Struct(song* P, FILE* fid);
void makeLowerCase(song Array[]);

int main(void) {
    int num, i, j = 0, k = 0;
    char quit = 'a', srch[10];
    song* songs, key, temp[2000];
    FILE* input;
    char word[50], word2[50];
    int count = 0;
    song* keyfound;
    int index[100];
    int year, rank;


    input = fopen("song_top100.txt", "r"); // opens file for reading

    if (input == NULL)
        printf("file not found\n");  // check to see if file is in correct place

    else {

        printf("Enter number of songs you want to use from the database: ");
        scanf("%d", &num);  // gets the number of songs user wants to search through

        songs = (song*)calloc(num, sizeof(int));

        keyfound = (song*)calloc(num, sizeof(int)); // I suspect these calloc functions are to blame for the stack overflow problems
                                                   // I free both songs and keyfound but it doesn't seem to help                                                                        

        for (i = 0; i < num; i++) {
            Load_Struct(&songs[i], input); // this calls a function that loads however many songs the user picked into the songs struct
        }


        while (quit != 'q' && quit != 'Q') { // this makes it interactive 

            printf("\n");
            printf("Enter:\n");
            printf("'key' to search song name with a keyword\n");
            printf("'artist' to search song(s) by artist\n");
            printf("'year' to search song(s) with top 5 in US rankings\n");
            printf("'rank' to search song(s) with US rankings\n");
            scanf("%s", &srch); // gets search criteria

            if ((srch[0] == 'k' || srch[0] == 'K') && (srch[1] == 'e' || srch[1] == 'E') && (srch[2] == 'y' || srch[2] == 'Y')) {
                 // if keyword search 
                // key can be lowercase or capital

                printf("Enter the keyword: ");
                scanf("%s", word); // gets keyword

                for (i = 0; i < num; i++) {
                    temp[i] = songs[i]; // saves songs into temp so doesn't get permanatly changed to lowercase
                }
                for (i = 0; i < 10; i++) {
                    word2[i] = word[i]; // saves keyword for same reason
                }
                k = 0;
                for (i = 0; i < num; i++) {

                    makeLowerCase(songs[i].name);
                    makeLowerCase(word); // changes both the keyword and all the song info to lowercase as to not have to worry about 
                                         // inconsistencies in case
                   
                    if (strstr(songs[i].name, word) != NULL) { // this does the actual keyword search
                        keyfound[count] = songs[i];
                        count++; 
                        index[k] = i;
                        k++;
                    }
                }
                for (i = 0; i < num; i++) {
                    songs[i] = temp[i]; // puts the unchanged song list back into songs
                }

                for (i = 0; i < count; i++) { 
                    keyfound[i] = temp[index[i]]; // this changes keyfound from the songs in all lowercase to how they were originally
                }

                for (i = 0; i < 50; i++) {
                    word[i] = word2[i]; // changes the keyword back to how the user typed it on 
                }
                if (count != 0) { // if results are found it prints them out
                    printf("%d songs with %s\n", count, word);
                    selection_sort(keyfound, count); // to display in order of year
                    for (i = 0; i < count; i++) {
                        printf("%s (%d) by %s, US(%d)\n", keyfound[i].name, keyfound[i].year, keyfound[i].artist, keyfound[i].us_rank);
                    }
                }
                else { // if nothing is found 
                    printf("No songs with %s in this database\n", word);
                }
            }

            else if ((srch[0] == 'a' || srch[0] == 'A') && (srch[1] == 'r' || srch[1] == 'R') && (srch[2] == 't' || srch[2] == 'T') &&
                (srch[3] == 'i' || srch[3] == 'I') && (srch[4] == 's' || srch[4] == 'S') && (srch[5] == 't' || srch[5] == 'T')) {
                // to search by artist name 
                // pretty much the same as the keyword search

                getchar();
                printf("Enter the artist name: ");
                fgets(word, 50, stdin); // had to use fgets because of space between first and last names

                word[strlen(word) - 1] = '\0'; // to get rid of \n

                for (i = 0; i < num; i++) {
                    temp[i] = songs[i];
                }
                for (i = 0; i < 50; i++) {
                    word2[i] = word[i];
                }

                k = 0;
                for (i = 0; i < num; i++) {

                    makeLowerCase(songs[i].artist);
                    makeLowerCase(word);
                    
                    if (strstr(songs[i].artist, word) != NULL) {
                        keyfound[count] = songs[i];
                        count++;
                        index[k] = i;
                        k++;
                    }
                }
                for (i = 0; i < num; i++) {
                    songs[i] = temp[i];
                }

                for (i = 0; i < count; i++) {
                    keyfound[i] = temp[index[i]];
                }

                for (i = 0; i < 10; i++) {
                    word[i] = word2[i];
                }

                if (count != 0) {
                    printf("%d songs by %s\n", count, word);
                    selection_sort(keyfound, count);
                    for (i = 0; i < count; i++) {
                        printf("%s (%d) by %s, US(%d)\n", keyfound[i].name, keyfound[i].year, keyfound[i].artist, keyfound[i].us_rank);
                    }
                }
                else {
                    printf("No songs by %s in this database\n", word);
                }
            }




            else if ((srch[0] == 'y' || srch[0] == 'Y') && (srch[1] == 'e' || srch[1] == 'E') && (srch[2] == 'a' || srch[2] == 'A') &&
                (srch[3] == 'r' || srch[3] == 'R')) {
                // search by year

                printf("Enter a year: ");
                scanf("%d", &year);
                k= 0;
                for (i = 0; i < num; i++) {
                    temp[i] = songs[i];
                }
                
                for (i = 0; i < num; i++) {
                    if (songs[i].year == year && songs[i].us_rank <= 5) { // if year is equal and rank is less than 5
                        keyfound[count] = songs[i];
                        count++;
                        index[k] = i;
                        k++;
                    }
                }

                for (i = 0; i < num; i++) {
                    songs[i] = temp[i];
                }

                for (i = 0; i < count; i++) {
                    keyfound[i] = temp[index[i]];
                }


                if (count != 0) {
                    printf("%d songs with top 5 ranking in %d\n", count, year);
                    for (i = 0; i < count; i++) {
                        printf("%s (%d) by %s, US(%d)\n", keyfound[i].name, keyfound[i].year, keyfound[i].artist, keyfound[i].us_rank);
                    }
                }
                else {
                    printf("No songs in %d in this database\n", year);
                }
            }
            else if ((srch[0] == 'r' || srch[0] == 'R') && (srch[1] == 'a' || srch[1] == 'A') && (srch[2] == 'n' || srch[2] == 'N') &&
                (srch[3] == 'k' || srch[3] == 'K')) {
                // to search by rank

                printf("Enter highest US ranking: ");
                scanf("%d", &rank);

                for (i = 0; i < num; i++) {
                    temp[i] = songs[i];
                }
                k = 0;
                for (i = 0; i < num; i++) {
                    if (songs[i].us_rank == rank) {
                        keyfound[count] = songs[i];
                        count++;
                        index[k] = i;
                        k++;
                    }
                }

                for (i = 0; i < num; i++) {
                    songs[i] = temp[i];
                }

                for (i = 0; i < count; i++) {
                    keyfound[i] = temp[index[i]];
                }


                if (count != 0) {
                    printf("%d songs with US ranking of %d\n", count, rank);
                    selection_sort(keyfound, count);
                    for (i = 0; i < count; i++) {
                        printf("%s (%d) by %s, US(%d)\n", keyfound[i].name, keyfound[i].year, keyfound[i].artist, keyfound[i].us_rank);
                    }
                }
                else {
                    printf("No songs with US rank %d\n", rank);
                }

            }

            else {
                printf("Choice not found\n");
            }

            printf("Continue (q/Q to quit)? "); // to end loop or not
            scanf(" %c", &quit);
        }

        free(songs); // by the time the program gets to this point it just kills itself
        free(keyfound); // it happened on my last lab too 
        fclose(input); // its not much of a problem because the program is done by this point anyway
    }

    return;
}



void swap(song* x, song* y) {
    song temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


void selection_sort(song x[], int size) {
    int i, j, max;
    for (i = 0; i < size; i++) {
        max = i;    
        for (j = i; j < size; j++) {
            if (x[j].year > x[max].year)  
                max = j;  
        }
        swap(&x[i], &x[max]);
    }
}

void Load_Struct(song* P, FILE* fid) {
    char waste;
    int i;

    fgets(P->name, 50, fid);
    fgets(P->artist, 50, fid);
    fscanf(fid, "%d %d", &P->year, &P->us_rank);
    fscanf(fid, "%c", &waste);

    for (i = 0; i < strlen(P->name); i++) {
        if (P->name[i] == '\n')
            P->name[i] = '\0';
    }
    for (i = 0; i < strlen(P->artist); i++) {
        if (P->artist[i] == '\n')
            P->artist[i] = '\0';
    }



    return;
}

void makeLowerCase(char name[]) {
    int i;

    for (i = 0; i < strlen(name); i++) {
        if (name[i] < 97 && name[i] >= 65 && name[i] <= 90) {
            name[i] += 32;
        }
    }
    return;
}