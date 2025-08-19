#include <stdio.h>

int main(void){

    float presVal, intRate, time, futVal;


    printf("\nHow much did you deposit? ");                             // present value prompt
    scanf("%f", &presVal);

    printf("At what annual interest rate? ");                           // interest rate prompt
    scanf("%f", &intRate);

    printf("How many years do you plan to keep it there? ");            // time prompt
    scanf("%f", &time);

    futVal = presVal * (1 + (intRate * time));                          // math to calculate future value 

    printf("The final value in the account will be: %.2f\n\n", futVal); // report furture value to user 

    return 0;
}