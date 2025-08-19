#include <stdio.h>

int main(void){

    float items[8], salesTax = 0, beforeTax = 0, afterTax = 0;
    int i, j;

    printf("\nPlease enter the price of 8 items (enter 8 items or enter 0 to end): "); 
    scanf("%f", &items[0]);                                     /// First prompt is different so not in loop

    for (i = 1; i < 8; i ++){                                   /// Loop to enter in up to 7 other numbers
        printf("Next item: ");
        scanf("%f", &items[i]);
        if (items[i] == 0 ){                                    /// if user enters 0 then the loop ends
            break;                                              /// I could not make it so the user just hits enter to end 
        }                                                       /// I attempted to use 10 instead of 0, along with '\n'
    }                                                           /// In both cases the loop only ended if the user entered 10

    printf("what is the local sales tax? ");
    scanf("%f", &salesTax);                                     /// user enters sales tax

    for (j = 0; j < i; j++){                                    /// loop to get total before tax
    beforeTax =  beforeTax + items[j];
    }
    
    afterTax = beforeTax + (beforeTax * (salesTax/ 100));       /// Math to get after tax
    
    printf("\nBefore Tax: %.2f\nAfter Tax: %.2f\n\n", beforeTax, afterTax); /// report to user

    return 0;
}