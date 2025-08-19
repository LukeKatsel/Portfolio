#include <stdio.h>
#include <time.h>

int main(void){

    time_t timer;

    time(&timer);   // get current time

    struct tm *gmTimer = gmtime(&timer);    // convert to struct tm 

    printf("The date and time is: %s", asctime(gmTimer));   // print as string

    return 0;
}