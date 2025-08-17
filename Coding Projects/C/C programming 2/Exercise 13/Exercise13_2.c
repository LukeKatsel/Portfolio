#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *FunctionPing(void *){

    while(1) {
        printf("Ping\n");
        sleep(1);
    }

    return NULL;
}

void *FunctionPong(void *){

    while(1) {
        printf("Pong\n");
        sleep(1);
    }

    return NULL;
}

int main(void){

    pthread_t threadPing;
    pthread_t threadPong;                           // create thread objects
    pthread_attr_t attr;

    pthread_attr_init(&attr);                       // set attributes

    pthread_create(&threadPing, &attr, &FunctionPing, NULL);
    pthread_create(&threadPong, &attr, &FunctionPong, NULL);    // create threads

    pthread_join(threadPing, NULL);                 // don't end main before threads are done
    pthread_join(threadPong, NULL);

    return 0;
}