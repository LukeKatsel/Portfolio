#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<math.h>

int main(void) {

/*	C file: hw1p1
	Author: Luke Katel
	Date created: 9/6/2021
	Brief description of the program: 
	This program takes a 4-digit number entered by the user and reverses the number to get a new number. 
	It then multiplies each digit from the first number to get the third number.
	This program finishes by taking the average of these three numbers and displays them for the user. 

	input(s): userNum
	output(s): userRev, prod, avg
	*/

int userNum;
int w;
int x;
int y;
int z;
double userRev;
double prod;
double avg;

printf("Enter a 4-digit number: ");
scanf("%d", &userNum);

w = userNum / 1000;				//this section is breaking userNum into each of its digits
x = (userNum / 100) % 10;
y = (userNum / 10) % 10;
z = (userNum % 10);

userRev = (z * 1000) + (y * 100) + (x * 10) + w;    // this line creates a number that is a reverse of userNum

prod = w * x * y * z;    // this creates the product of the all 4 digits

avg = (userNum + userRev + prod) / 3;  // this creates the average of the 3 numbers

printf("average of %d, %.0lf, %.0lf, is %.2lf\n", userNum, userRev, prod, avg);   // this brings it all together and displays it for the user

return(0);
}
