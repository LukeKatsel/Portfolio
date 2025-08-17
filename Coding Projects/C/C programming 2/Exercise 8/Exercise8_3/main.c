#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
    float root;
    float userNum;

    if (argc != 2){
        printf("\nWrong number of argumants\n");
        return 1;
    }

    userNum = strtof(argv[1], NULL);

    root = sqrt(userNum);

    printf("\nThe Square Root of %f is %f\n\n", userNum, root);

    return 0;
}