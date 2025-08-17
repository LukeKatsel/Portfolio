#include<stdio.h>
#include<math.h>

int main(void){

int a = 0;
int b = 0;
int c = 0;

printf("Enter your Numbers:\n");

if (scanf("%d%d", &a, &b)!= 2) {
    printf("Not a number!\n");
}
else{
    c = (int)pow(a, 3) + b;
    printf("C is equal to:%d\n", c);

}
    return 0;
}