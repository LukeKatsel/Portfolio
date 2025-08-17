#include <stdio.h>


void eighties(void){
    printf("U2, R.E.M.");
}

void nineties(void){
    printf("Counting Crows, Matchbox Twenty");
}


int main(void){

    eighties();
    printf(", ");
    nineties();
    printf("\n");
    nineties();
    printf("\n");
    eighties();
    printf("\n");
}