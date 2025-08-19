#include <stdio.h>
#include <time.h>

int main(void){

    struct tm moonLanding;      // create struct tm object

    moonLanding.tm_sec=0;
    moonLanding.tm_min=0;
    moonLanding.tm_hour=23;
    moonLanding.tm_mday=20;
    moonLanding.tm_mon=6;           // set date to july 20 1969
    moonLanding.tm_year=69;
    moonLanding.tm_hour=0;
    moonLanding.tm_wday=1;
    moonLanding.tm_yday=201;
  
    time_t timer = mktime(&moonLanding);        // set to time_t object 

    printf("The first moon landing was %s", ctime(&timer));   // print as string

    return 0;
}