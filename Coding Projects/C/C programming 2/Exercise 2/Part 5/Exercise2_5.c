#include<stdio.h>

int main(void){
    int i, wage, groc, util, phone, other, rent, expenses;
    float hours, income;

    printf("What is your hourly wage? ");
    scanf("%d", &wage);
    printf("How many hours per week do you work? ");
    scanf("%e", &hours);
    printf("How much do you spend on groceries each week? ");
    scanf("%d", &groc);
    printf("What is your monthly utility bill? ");
    scanf("%d", &util);
    printf("What is your monthly cell phone bill? ");
    scanf("%d", &phone);
    printf("What other expenses do you have this month? ");
    scanf("%d", &other);
    printf("How much is your rent? ");
    scanf("%d", &rent);

    if (hours > 40){
        hours = ((hours - 40) * 1.5) + 40;
    }

    income = (hours * 4)  * wage;

    expenses = groc + util + phone + other;

    if ((income - expenses) >= rent){
        printf("\nYou can pay rent!!\n\n");
    }

    else{
        printf("\nBetter get back to work!!\n\n");
    }

    return 0;
}