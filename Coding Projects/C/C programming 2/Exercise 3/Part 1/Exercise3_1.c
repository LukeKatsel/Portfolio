#include <stdio.h>

int main(void){

    FILE *file;
    char fileChar; 
    int spaces = 0, newline = 0, period = 0, other = 0; /// initializing the counters 

    file = fopen("Exercise3_1.txt", "r");               /// opening the file for reading

    while(((fileChar = fgetc(file)) != 94 && 126)){     /// keep reading one character at a time until we encounter a ^ or ~
        if (fileChar == 32){                            /// if the character is a space increment counter
            spaces++;
        }
        else if (fileChar == 10){                       /// if the character is a newline increment counter
           newline++;
        }
        else if (fileChar == 46){                       /// if the character is a period increment counter
            period++;
        }
        else                                            /// if the character is anything else increment counter
            other++;
    }

    printf("\nNumber of spaces: %d\nNumber of Newline characters: %d\nNumber of Periods: %d\nNumber of other characters: %d\n\n", spaces, newline, period, other);

    fclose(file);                                       /// report to user and close file

    return 0;
}