#include <stdio.h>


int main(void){

    FILE *file;
    char fileChar;
    float wordCount = 0, charCount = 0, charAvg = 0;


    file = fopen("Exercise3_3.txt", "r");           // open file for reading

    while((fileChar = fgetc(file)) != EOF){         // Keep going character by character until we reach the end of the file
       switch (fileChar){                           // if the value in fileChar is:
        case 32:                                    // 32 (a space) 
            wordCount++;                            // increment the word counter
            break;
        case 10:                                    // 10 (\n)
            wordCount++;                            // increment the word counter
            break;
       default:                                     // anything else
            charCount++;                            // increment the character counter
        break;
       }
    }
    charAvg = (charCount / wordCount);              // math to get average 

    printf("\nTotal Non-whitespace characters: %.0f\nTotal Words: %.0f\nAverage characters per word: %.1f \n\n", charCount, wordCount, charAvg);

    fclose(file);                                   // report to user and close file

    return 0;                                       
}