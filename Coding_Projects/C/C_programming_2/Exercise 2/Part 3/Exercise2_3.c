#include<stdio.h>
#include<math.h>

int main(void){
    float heightCm = 0, heightIn = 0, calc = 30.48, rem = 0;
    float heightFt = 0;

    printf("Enter a height in centimeters (<=0 to quit): ");
    scanf("%f", &heightCm);

    if (heightCm <= 0){

        printf("Bye\n");
        return 0;
    }
    else{

        heightFt = heightCm / calc;
        rem = heightFt - (int)heightFt;
        heightIn = rem * 12;
        printf("%.1f cm = %d feet, %.1f inches\n", heightCm, (int)heightFt, heightIn);

    }
    return 0;
}


//  gcc -o Exercise2_3 Exercise2_3.c -lm