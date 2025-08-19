#include <stdio.h>
#include <time.h>

int main(void){

    time_t timer;

    time(&timer);           // get current time

    printf("The time and date is currently: %s", ctime(&timer)); // print current time as string w/ ctime()

    return 0;
}