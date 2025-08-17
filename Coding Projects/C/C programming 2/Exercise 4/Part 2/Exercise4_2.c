#include <stdio.h>
#include <ctype.h>

int main(void){

    int year, isLeap;

    printf("Enter year:");

    if (scanf("%d", &year) != 1 || isdigit(year)){          // simple input validation
        printf("Not a valid input");
    }
    else{

        if (year % 4 != 0){                                 // condition 1
            isLeap = 0;
        }
        else if (year % 100 != 0){                          // condition 2
            isLeap = 1;
        }
        else if(year % 400 != 0){                           // condition 3
            isLeap = 0;
        }
        else{                                               // else
            isLeap = 1;
        }
    }
    if (isLeap == 1){
        printf("%d is a Leap Year\n", year);                // if leap year
    }
    else{
        printf("%d is not a Leap year\n", year);            // if not
    }
    return 0;
}