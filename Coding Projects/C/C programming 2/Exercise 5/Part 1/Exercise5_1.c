#include <stdio.h>
#include <ctype.h> 

int main(int argc, char *argv[]){

    FILE *file;
    FILE *file2;

    if ((file = fopen(argv[1], "r")) != NULL){          // open file for reading
        if ((file2 = fopen(argv[2], "w")) != NULL){     //open second file for writing
            while (!feof(file)){                        // while we havent reached the end of the file
                fputc(toupper(fgetc(file)), file2);     // get character from file 1, set to uppercase, and print to file 2
            }
            fclose(file2);                              // close file 2
        }
        else{
            printf("Could not open file 2");
        }
        fclose(file);                                   // close file 1
    }
    else{
        printf("Could not open file 1");
    }
    return 0;
}