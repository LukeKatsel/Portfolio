#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main(void) {

	/*
	C file: hw1p2
	Author: Luke Katsel
	Date created: 9/6/2021
	Brief description of the program: This program takes the maximum height and initial velocity from the user and outputs the angle of fire and maximum horizontal distance.
	input(s): maximum height, initial velocity
	output(s): angle of fire, maximum horizontal distance
	*/

	double maxH;
	double iniVel;
	double angle;
	double angle2;
	double maxHor;
	double g = 9.80665;
	double pi = 3.14159265;
	
	printf("Enter a maximun height (in m): ");
	scanf("%lf", &maxH);

	printf("Enter an initial velocity (in m/s): ");
	scanf("%lf", &iniVel);

	angle = asin(sqrt((maxH * (2 * g)) / pow(iniVel, 2))); // this line calculates the angle of fire in radians using the maximum height and initial velocity

	angle2 = angle * 57.2958;   // this converts radians to degrees

	maxHor = (pow(iniVel, 2) * sin(2 * angle)) / g;	  //this calculates the maximum horizontal distance using the angle calculated above
	
	printf("We should fire the ball at angle of %.2lf degrees\n", angle2);
	printf("The maximum horizontal distance is %.4lf m\n", maxHor);

	return(0);
}
