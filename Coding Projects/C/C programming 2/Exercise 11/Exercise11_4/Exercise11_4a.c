 #include <stdio.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/stat.h>
 #include <semaphore.h>

 #define FILE "BtoAtoB.txt"
 #define MESSAGE "Hello B"
 #define MAX_MESSAGE_SIZE 16

int main(void){
   
    sem_t *mutex;
    if((mutex = sem_open(FILE, O_CREAT | O_RDWR, 0666, 1)) == SEM_FAILED){  // create semaphore

        printf("ERROR opening semaphore: %s\n", FILE);
        return 1;
    }

    int file_fd;
    if((file_fd = open(FILE, O_CREAT | O_RDWR, 0666)) == -1){

        printf("ERROR opening file: %s\n", FILE);
        return 1;
    }

    ssize_t bytesWritten = write(file_fd, MESSAGE, strlen(MESSAGE));
    if (bytesWritten == -1){
                
        printf("ERROR writing to file: %s\n", FILE);
        return 3;
    }
    
    char receivedMessage[MAX_MESSAGE_SIZE];

        while (1){

            if (sem_wait(mutex) == 0){      // get and hold semaphore
                
                lseek(file_fd, 0, SEEK_SET);

                ssize_t bytesRead = read(file_fd, receivedMessage, MAX_MESSAGE_SIZE);
                if ((bytesRead > 0) && (strcmp(receivedMessage, MESSAGE) != 0)){

                    receivedMessage[bytesRead] = '\0';
                    printf("%s\n", receivedMessage);

                    sleep(1);

                    lseek(file_fd, 0, SEEK_SET);
                    bytesWritten = write(file_fd, MESSAGE, strlen(MESSAGE));
                    if (bytesWritten == -1){
                    
                        printf("ERROR writing to file: %s\n", FILE);
                        return 3;
                    }
                }
                sem_post(mutex);        // release semaphore
            }
        }

    sem_destroy(mutex); // destroy semaphore
    close(file_fd);

    return 0; 
}