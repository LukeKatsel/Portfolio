#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>


//Author: Luke Katsel
//Date created: 10/5/2021
//Brief description of the program: This program takes inputs from a txt document and translates it into a user type and water amount to calculate the water bill
//input(s): user type and water amount from .txt doc
//output(s): amount on water bill from function water_billcalculation




double water_billcalculation(char type, double water) {       // this is my fuction; basically just my hw2p2 copied and pasted here
    double beforeTax = 0;
    double afterTax = 0;


    if (type == 'R' || type == 'r') {   // if user type is residential 
        if (water <= 400) {
            beforeTax = (0.04 * water) + 13.50;
        }
        else if (water <= 700) {
            beforeTax = (0.062 * (water - 400)) + 13.50 + 29.5;
        }
        else {
            beforeTax = (0.12 * (water - 700)) + 13.50 + 48.1;
        }
    }

    else if (type == 'G' || type == 'g') {  // if user type is government
        beforeTax = (0.035 * water) + 3.75;
    }

    else if (type == 'B' || type == 'b') {  // if user type is business
        beforeTax = (0.0553 * water) + 17.25;
    }

    else {
    }

    afterTax = beforeTax + (beforeTax * 0.087);


    return afterTax;
}

int main(void) {        // main body


    FILE* fileinput;
    char type;
    double water;
    double beforeTax = 0;
    double afterTax = 0;

    fileinput = fopen("water_usage.txt", "r");      // this opens the doc
    if (fileinput == NULL) {
        printf("file not found\n");
    }
    else {

        while (fscanf(fileinput, "%c %lf ", &type, &water) != EOF) {        // this while loop is what scans the doc and prints the output
            if (type == 'B' || type == 'b' || type == 'G' || type == 'g' || type == 'R' || type == 'r') {
                printf("%c              %.0lf               %.2lf\n", type, water, water_billcalculation(type, water));

            }
            else {
                printf("%c              Wrong User Type\n", type);
            }
        }
    }

    
    fclose(fileinput);



    return(0);
}


