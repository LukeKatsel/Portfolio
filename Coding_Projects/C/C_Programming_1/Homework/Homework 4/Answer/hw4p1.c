#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main(void) {
    FILE* fileinput;
    int fileContents;
    char fileContents2;

    fileinput = fopen("Ascii_Art_Compressed.txt", "r");
    if (fileinput == NULL) {
        printf("file not found\n");
    }
    else {

        while (fscanf(fileinput, "%d%c", &fileContents, &fileContents2) != EOF) {
            while (fileContents != 0) {
                printf("%c", fileContents2);
                fileContents--;
            }
        }
    }
    fclose(fileinput);

    return(0);
}