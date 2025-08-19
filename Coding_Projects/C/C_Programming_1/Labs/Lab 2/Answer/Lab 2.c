#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>

int main(void) {

    /*double A, B, C;

    printf("Enter in three sides of a triangle A,B,C: ");
    scanf("%lf %lf %lf", &A, &B, &C);

    if (A + B > C && B + C > A & C + A > B) {
        if (A == B && B == C)
            printf("Sides A = %.2lf, B = %.2lf, C = %.2lf will form an equilateral triangle\n", A, B, C);

        else if (A == B || A == C || B == C)
            printf("Sides A = %.2lf, B = %.2lf, C = %.2lf will form an isosceles triangle\n", A, B, C);
        
        else 
            printf("Sides A = %.2lf, B = %.2lf, C = %.2lf can be formed into a triangle\n", A, B, C);
    }
    else
    printf("Sides A = %.2lf, B = %.2lf, C = %.2lf cannot be formed into a triangle\n", A, B, C);*/
        












   /* int N;
    int i;
    int max = 250;
    int sum = 0;
    int total = 0;


    printf("Enter a value for N: ");
    scanf("%d", &N);

    for (i = 10; i <= max; i = i + 1) {
        if (i % N == 0) {
            sum = sum + i;
            total = total + 1;
        }
    }
    
    printf("There are %d values between 10-250 that are divisible by %d \n", total, N);
    printf("Sum of numbers between 10 - 250 that are divisible by %d is %d\n", N, sum);*/












    int P;
    int N = 2;
    int M;
    int sum = 0;

    printf("How many digits? ");
    scanf("%d", &P);

    M = pow(10, P - 1);

    while (sum < pow(10, P - 1)) {
      sum = sum + N;
      N = N + 2;
       
    }

    N = N - 2;

    printf("Find smallest N >= %d\n", M);

    printf("N = %d      ", N);

    printf("Sum = %d\n", sum);

    return(0);
}