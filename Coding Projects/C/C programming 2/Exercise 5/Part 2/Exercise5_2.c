#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    FILE *file;
    int offset = atoi(argv[2]);         // get the offset and maxChar from command 
    int maxChar = atoi(argv[3]);        // use atoi to get full integer entered by user
    char buffer[maxChar];

    if ((file = fopen(argv[1], "r")) != NULL){
        fseek(file, offset, SEEK_SET);      // start at beinning of file and skip to "offset" number of bytes in 
        fread(buffer, 1, maxChar, file);    // read "maxChar number of bytes into the buffer variable"
        printf("\n%s\n\n", buffer);         // print buffer 
        fclose(file);                       // close file
    }
    else{
        printf("Could not open file!\n");
    }
    return 0;
}