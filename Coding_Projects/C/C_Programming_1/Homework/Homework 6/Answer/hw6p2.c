#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>



//Author: Luke Katsel
//Date created: 10/19/2021
//Brief description of the program: program opens 2 text docs and finds the mean and standard deviation of each, then the correlation between the two
//input(s): two text docs with 500 numbers
//output(s): mean and standard deviation of each and the correlation between the two



void read_file(FILE* inp, double z[], int length) { // reads the data into an array
	int i;
		for (i = 0; i < length; i++) {
			fscanf(inp, "%lf ", &z[i]);
		}	
}

void calc_mean(int length, double z[], double* mean) { // finds the mean
	int i;
	double sum = 0;

	*mean = 0;

	for (i = 0; i < length; i++) {
		sum = sum + z[i];
	}

	*mean = sum / length;
}


void calc_std(int length, double z[], double* std){ // finds the standard deviation
	
	int i;
	double temp = 0, sum = 0, mean, equ = 0;

	for (i = 0; i < length; i++) {
		sum = sum + z[i];
	}

	mean = sum / length;

	for (i = 0; i < length; i++) {
		temp = temp + pow((z[i] - mean), 2);
	}



	temp = temp / (length);

	*std = sqrt(temp);
}



int main(void) {
	FILE* inp;
	double z[500];
	double z2[500];
	double file = 1.;
	int count = 500;
	int i;
	double t;
	double mean1 = 0, mean2 = 0;
	double std1, std2, corr, calc = 0;

	inp = fopen("data1.txt", "r"); // opens the first file

	if (inp == NULL) {
		printf("file not found\n");
	}
	else {
		read_file(inp, z, count); // reads in 

		calc_mean(count, z, &mean1); // calculation

		calc_std(count, z, &std1); //calculation

	}

	fclose(inp); // closes file


	inp = fopen("data2.txt", "r"); // opens file 2

	if (inp == NULL) {
		printf("file not found\n");
	}
	else {
		read_file(inp, z2, count); // reads in 

		calc_mean(count, z2, &mean2); //calculation

		calc_std(count, z2, &std2);// calculation

	}
	fclose(inp); // closes file 2

	for (i = 0; i < count; i++) { // this part calculates the correlation
		calc = calc + ((z[i] - mean1) * (z2[i] - mean2));
	}
	corr = calc / (std1 * std2);
	corr = corr / 500;

	printf("Mean of data in data1.txt is %.8lf\n", mean1); // prints out the results 
	printf("Mean of data in data2.txt is %.8lf\n", mean2);
	printf("Standard deviation of data in data1.txt is %.8lf\n", std1);
	printf("Standard deviation of data in data2.txt is %.8lf\n", std2);
	printf("The correlation is %.8lf\n", corr);
	

	return(0);
}
