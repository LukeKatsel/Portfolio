#include<stdio.h>

int main(void){
    int i, j, arr[7], arr2[7];

    
    for (i = 0; i < 7; i++){
        j = i + 1;
        printf("Enter a number for Array spot %d: ", j);
        scanf("%d", &arr[i]);
    }
    printf("\n");
    j = 0;

    for (i = 0; i < 7; i++){
        arr2[i] = arr[i] + j;
        j = arr2[i];
        printf("%d\t", arr[i]);
    }
    printf("\n");
    for (i = 0; i < 7; i++){
        printf("%d\t", arr2[i]);
    }

    return 0;
}