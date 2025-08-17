#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main(void) {

	/*
	int a;
	int b;
	int c;

	printf("Enter three integers: ");
	scanf("%d %d %d", &a, &b, &c);

	if ((a < b) && (a < c)) {
		printf("Minimum is %d\n", a);
		b = b - a;
		c = c - a;
		a = a - a;
	}
	else if ((b < a) && (b < c)) {
		printf("Minimum is %d\n", b);
		a = a - b;
		c = c - b;
		b = b - b;
	}
	else {
		printf("Minimum is %d\n", c);
		a = a - c;
		b = b - c;
		c = c - c;
	}
	 
	printf("New numbers are: %d %d %d\n", a, b, c);*/

	

	

	int speed;
	double fine;

	printf("Enter the speed: ");
	scanf("%d", &speed);

	if (speed >= 90) {
		fine = (speed + speed * 0.4);
		printf("Fine ammount is: $%.2lf\n", fine);
	}
	else if (speed >= 80) {
		fine = (speed + speed * 0.3);
		printf("Fine ammount is: $%.2lf\n", fine);
	}
	else if (speed >= 70) {
		printf("Fine ammount is: Warning\n");
	}
	else 
		printf("Fine ammount is: No Fine\n");
	


	return(0);
}