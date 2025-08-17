#include <stdio.h>
#include <string.h>

int CharLocation(char userChar);
void PrintHex (char userChar, int location);


int CharLocation(char userChar){                            // Function to find Location of letter in alphabet

    if ((userChar >= 65) && (userChar <= 90)){              // if Uppercase 
        userChar = userChar - 64;                           // subtract 64 to get location
    }
    else if ((userChar >= 97) && (userChar <= 122)){        // if lowercase
        userChar = userChar - 96;                           // subtract 96 to get location
    }
    else{                                                   // anything else 
        userChar = -1;                                      // set to -1
    }
    return userChar;                                        // return userChar, which is now set to location of letter in alphabet
}                                                           // function returns integers so don't need to worry about userChar actually is now



void PrintHex (char userChar, int location){                // function to print hex value and location

    if (userChar == 10){                                    // if character is newline, don't print a newline  
        printf("Character: \t");
    }
    else{                                                   // otherwise just print character
        printf("Character: %c\t", userChar);
    }

    printf("Hex value: %x\t", userChar);                    // print hex value

    if (location == -1){                                    // if not a letter, say so
        printf("Not a letter\n");
    }
    else{                                                   // otherwise report location
        printf("Location in alphabet: %d\n", location);
    }
}


int main(void){

  FILE *file;
    char fileChar, fileName[50], userString[200], userChar, temp;
    int userChoice, location, i;
    
    printf("\nCharacter conversion to hexadecimal\n");
    printf("Would you like to input file(enter 0)? or type in string(enter 1)? Enter anything else to end program: ");
    scanf("%d", &userChoice);                               // user can use file or enter a string

    if (userChoice == 0){                                   // if user entered 0 to input file

        printf("Enter file name: ");
        scanf("%s", fileName);
        strcat(fileName, ".txt");                           // adds .txt so user doesn't need to

        file = fopen(fileName, "r");                        // open file for reading

        while((fileChar = fgetc(file)) != EOF){             // keep getting charaters until we reach the end

            location = CharLocation(fileChar);              // input character into CharLocation function above
            PrintHex(fileChar, location);                   // input character and location into PrintHex function

        }
    }
    else if (userChoice == 1){                              // if user entered 1 to enter string
        printf("Type the string or character: ");
        scanf("%c",&temp);                                  // need to clear buffer to use fgets
        fgets(userString, 200, stdin);                      // use fgets to get whole string, not just stop at first space
        for(i = 0; i < strlen(userString); i++){            // itterate through string
            
            userChar = userString[i];
            location = CharLocation(userChar);              // user CharLocation function
            PrintHex(userChar, location);                   // use PrintHex function
        }
    }
    else{                                                   // not really needed, but makes me feel better having it
    }
    return 0;
}