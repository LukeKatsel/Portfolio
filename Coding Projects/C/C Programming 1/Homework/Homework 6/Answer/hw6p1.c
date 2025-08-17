#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

#define ALen 20



//Author: Luke Katsel
//Date created: 10/19/2021
//Brief description of the program: This program opens a file containing security codes and runs the luhn algorithm on them to test if valid.
//input(s): SecurityCodes.txt
//output(s): outputs the security code and if it is valid or not.




void arrayFlipper(int ArrayIn[], int ArrayOut[], int L) { // this array flipping program makes it easier to read the codes
	int i;

	for (i = 0; i < L; i++) {
		ArrayOut[i] = ArrayIn[L - 1 - i];
	}

	return;
}

int ReadSecurityCode(FILE *I, int SC[]) { // this program reads in the codes into an array
	int i;

	for (i = 0; i < ALen; i++) {
		fscanf(I, "%d", &SC[i]);
	}

	return SC;
}

int IsValidSecurityCode(int SC[]) {  // this program runs the luhn algorithm
	int i, j, sumOdd = 0, sumEven = 0, sumTotal = 0, valid = 1;

	for (i = 0; i < ALen; i += 2) {
		j = i + 1;
		sumOdd = sumOdd + SC[i];
		if ((SC[j] * 2) >= 10) {
			sumEven = sumEven + ((SC[j] * 2) % 10) + ((SC[j] * 2) / 10);
		}
		else {
			sumEven = sumEven + (SC[j] * 2);
		}
	}

	sumTotal = sumEven + sumOdd;

	if (sumTotal % 10 == 0) {
		valid = 0;
	}
	
	return valid;
}



int main(void) {
	int Array[ALen], FlippedArray[ALen];
	FILE* I;
	int i, j, k;
	int sumOdd = 0, sumEven = 0, sumTotal = 0, num = 0;
	int valid = 1;
	int t;

	I = fopen("SecurityCodes.txt", "r");  // opens the text doc
	
	for(k = 0; k < 45; k++){  // this loop is what makes the algorithm read all the codes 
		ReadSecurityCode(I, &Array); // reads in codes

		printf("\n");

		arrayFlipper(Array, FlippedArray, ALen); // flips array

		for (i = 0; i < ALen; i++) {
			printf("%d ", Array[i]); // prints out array
		}

		printf("\t");


		for (i = 0; i < ALen; i += 2) { // this part calculates what number the last number should have been to be a valid code
			j = i + 1;
			sumOdd = sumOdd + FlippedArray[i];
			if ((FlippedArray[j] * 2) >= 10) {
				sumEven = sumEven + ((FlippedArray[j] * 2) % 10) + ((FlippedArray[j] * 2) / 10);
			}
			else {
				sumEven = sumEven + (FlippedArray[j] * 2);
			}
		}

		sumTotal = sumEven + sumOdd;

		
			num = Array[ALen -1] + 10 - (sumTotal % 10); 

			if (num > 10) {
				num = num - 10;
			}
			else if (num == 10) {
				num = num - 1;
			}
	
		

		if (IsValidSecurityCode(FlippedArray)) { // this prints out if the code is valid or not 
			printf("invalid\n");
			printf("The digit in the first position for valid code should be %d", num);
		}
		else {
			printf("valid");
			
		}
		
	} 

	return(0);
}