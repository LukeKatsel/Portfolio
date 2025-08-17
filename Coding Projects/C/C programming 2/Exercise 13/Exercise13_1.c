#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *function(void *){

    while(1) {
        printf("hello world\n");
        sleep(1);
    }

    return NULL;
}

int main(void){

    pthread_t thread;                       // create thread object
    pthread_attr_t attr;

    pthread_attr_init(&attr);               // set attributes
    pthread_create(&thread, &attr, &function, NULL);    // create thread

    pthread_join(thread, NULL);             // don't end main before threads are done

    return 0;
}