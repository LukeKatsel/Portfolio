#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>


//Author: Luke Katsel
//Date created: 10/25/2021
//Brief description of the program: user enters a statement and this counts the words and flips the sentence
//input(s): a user made statement
//output(s): word count and flipped statement


int main(void) {
    char userString[50];
    char userStringFlip[50];
    int i, j = 0, count = 0, length, begin, end;

    printf("Enter a statement: ");
    fgets(userString, 50, stdin); // user enters statement

    length = strlen(userString); // assigns length with length of user statement

    for (i = 0; i < length; i++) { // this is the counter
        if (userString[i] == '\n') {
            userString[i] = ' ';
        }
        userStringFlip[i] = ' ';
        if (userString[i] == ' ' || userString[i] == '\n') {
            count += 1;
        }
    }

    begin = length - 1;
    end = length - 1; // initialize both begin and end with length of sentence - 1

    while (begin > 0) {
        if (userString[begin] == ' ') { //looks for spaces
            i = begin + 1;
            while (i <= end ) {// this is what does the flipping
                userStringFlip[j] = userString[i];
                    i++;
                    j++;
            }
            userStringFlip[j++] = ' ';
            end = begin - 1;
        }
        begin--; // deincrements begin
    }

    for (i = 0; i < end + 1; i++) { // this part is needed to include the last word
        userStringFlip[j] = userString[i];
        j++;
    }

    userStringFlip[j] = '\0'; // puts the end character back 

    printf("%s\n", userStringFlip); // prints out result
    printf("There are %d words in the statement\n", count);

    return;
}