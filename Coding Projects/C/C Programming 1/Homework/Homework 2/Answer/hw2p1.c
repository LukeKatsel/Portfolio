#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main(void) {
    
//Author: Luke Katsel
//Date created: 9/13/2021
//Brief description of the program: This program calculates the Julian day number from a date input
//input(s): any date in form mm/dd/yyyy
//output(s): Julian day number

    int mm;
    int dd;
    int yyyy;
    int A;
    int B;
    int C;
    int D;
    double JD;


    printf("Enter a date of the form mm/dd/yyyy ");
    scanf("%d/%d/%d", &mm, &dd, &yyyy);         // this is where the user enters their input

    if (mm <= 2) {      // this if statement takes january and febuary dates and  
        yyyy = yyyy - 1;    //subtracts 1 from the year and adds 12 to the month
        mm = mm + 12;
    }

    A = yyyy / 100;

    B = 2 - A + (A / 4) + dd;

    C = 365.25 * (yyyy + 4716);

    D = 30.6001 * (mm + 1);         // these equations are straight from the hw sheet

    JD = B + C + D - 1524.5;

    if ((mm == 13) || (mm == 14)) {  // this if statement is to reverse the if statement above so
        yyyy = yyyy + 1;            // that the date in the printf statement below displays correcty 
        mm = mm - 12;
    }

    printf("For the date %d/%d/%d, the value of B is %d, and the Julian Day Number is %.1lf \n", mm, dd, yyyy, B, JD);


    return(0);
}
