#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

void *FunctionPing(void *){

    int i = 0;
    char str[6] = "ping";

    while (1){

        putc(str[i], stdout);                       // print one char at time 
        fflush(stdout);                             // clear buffer
        i = ((i + 1) % strlen(str));                // increment/ decrement i so it loops through size of str
        usleep(100000);
    }

    return NULL;
}

void *FunctionPong(void *){

    int i = 0;
    char str[6] = "pong";

    while (1){

        putc(str[i], stdout);                       // print one char at time 
        fflush(stdout);                             // clear buffer
        i = ((i + 1) % strlen(str));                // increment/ decrement i so it loops through size of str
        usleep(100000);
    }

    return NULL;
}

int main(void){

    pthread_t threadPing;                           // create thread objects
    pthread_t threadPong;
    pthread_attr_t attr;

    pthread_attr_init(&attr);                       // set attributes

    pthread_create(&threadPing, &attr, &FunctionPing, NULL);
    pthread_create(&threadPong, &attr, &FunctionPong, NULL);    // create threads

    pthread_join(threadPing, NULL);                 // don't end main before threads are done
    pthread_join(threadPong, NULL);

    return 0;
}