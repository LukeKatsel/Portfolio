#include <stdio.h>
#include <errno.h>

int main (void){

    FILE *file; // file pointer

    rename("file.txt", "VeryUnliklyToHaveAFileNamedThis.txt");

    file = fopen("file.txt", "r");    // open file that does not exist

        if (file == NULL){              

        printf("Error number: %d\n", errno);    // print error number
        perror("ERROR");                        // print error message
    }

    rename("VeryUnliklyToHaveAFileNamedThis.txt", "file.txt");

    return 0;
}