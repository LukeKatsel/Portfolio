#include <stdio.h>
#include <time.h>

int Delay(double time);

int main(void){
    double delayTime = 0;

    while (1){
        printf("Enter delay time (- value to end): ");       // prompt user
        if (scanf("%lf", &delayTime) == 1){             // scan in user input
            if (delayTime < 0){                       // if user enters a negative number then break and end program
                break;
            }
            else{                                       // if user enters a valid number then we will go into delay program
                if ((Delay(delayTime)) == -1){
                    puts("Clock failed!\n");
                    return 0;
                }
            }
        }
        else{                                           // if user enters an invalid value then break and end program
            printf("Not a valid Value\n");
            break;
        }
    }

    return 0;
}

int Delay(double time){
    double start= clock(), curTime = 0, diff = 0;      

    if (clock() == -1){
        return -1;
    }
    else{
        while (diff != time){    // keep looping until the ((current time - start time) / CLOCKS_PER_SEC) equals the time the user entered
                                                        
            curTime = clock();                             // keep updating current time 
            diff = (curTime - start) / CLOCKS_PER_SEC;
        }
        return 0;
    }
}