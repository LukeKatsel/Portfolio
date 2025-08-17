#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main(void) {

    //Author: Luke Katsel
    //Date created: 9/13/2021
    //Brief description of the program: This program calculates the water bill from user inputs.
    //input(s): User type and amount of water used
    //output(s): before tax cost and after tax cost

    char type;
    int water;
    double beforeTax;
    double afterTax;


    printf("Enter User Type (R for Residential, B for Business, G for Government): ");
    scanf("%c", &type);

    printf("Enter water usage in cubic feet: ");
    scanf("%d", &water);                                // this is where user inputs values


    if (type == 'R') {  // this executes if user enters E
        if (water <= 400)
            beforeTax = (0.04 * water) + 13.50;

        else if (water <= 700)
            beforeTax = ((water - 400) * 0.062) + 13.50 + 16;       //  these are the three different prices within residential 

        else
            beforeTax = (0.12 * (water - 700)) + 13.50 + 34.6;

        afterTax = beforeTax + (beforeTax * 0.087);

        printf("Total cost before tax is $%.2lf\n", beforeTax);

        printf("Total cost including tax is $%.2lf\n", afterTax);

    }

    else if (type == 'G') {     // this only executes if user enters G
        beforeTax = (0.035 * water) + 3.75;

        afterTax = beforeTax + (beforeTax * 0.087);

        printf("Total cost before tax is $%.2lf\n", beforeTax);

        printf("Total cost including tax is $%.2lf\n", afterTax);
    }

    else if (type == 'B') {         // this only executes if user enters B
        beforeTax = (0.0553 * water) + 17.25;

        afterTax = beforeTax + (beforeTax * 0.087);     // I had to include all of these equations in each of the if statements to keep from 
                                                        // from trying to be executed if the user didnt enter G, B, or R
        printf("Total cost before tax is $%.2lf\n", beforeTax);

        printf("Total cost including tax is $%.2lf\n", afterTax);
    }

    else {          // this executes if the user enters anything but G, B, or R
        printf("Wrong user type\n");
    }



    return(0);
}