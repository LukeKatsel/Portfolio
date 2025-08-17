 #include <stdio.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <string.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <errno.h>

 #define IN_FIFO "FIFO_AB"
 #define OUT_FIFO "FIFO_BA"
 #define MESSAGE "\tHello A"
 #define MAX_MESSAGE_SIZE 16

int main(void){
   
    int outFile_fd;
    int inFile_fd;

    if(((mkfifo( OUT_FIFO, 0664)) == -1) && (errno != EEXIST)){ // make OUT_FIFO

        printf("ERROR Making FIFO: %s\n ERRNO:%s", OUT_FIFO, strerror(errno)); 
        return 1;
    }

    if(((mkfifo( IN_FIFO, 0664)) == -1) && (errno != EEXIST)){ // make IN_FIFO

        printf("ERROR Making FIFO: %s\n ERRNO:%s", IN_FIFO, strerror(errno)); 
        return 1;
    }
    
    if(((outFile_fd = open(OUT_FIFO, O_WRONLY | O_NONBLOCK)) == -1)){ // open OUT_FIFO and set  equal to outFile_fd

        printf("ERROR opening FIFO: %s\n ERRNO:%s", OUT_FIFO, strerror(errno)); 
        return 1;
    }
    if(((inFile_fd = open(IN_FIFO, O_RDONLY | O_NONBLOCK)) == -1)){ // open IN_FIFO and set  equal to inFile_fd

        printf("ERROR opening FIFO: %s\n ERRNO:%s", IN_FIFO, strerror(errno)); 
        return 1;
    }

    ssize_t bytesWritten;
   
    char receivedMessage[MAX_MESSAGE_SIZE];

    while (1){

        ssize_t bytesRead = read(inFile_fd, receivedMessage, MAX_MESSAGE_SIZE);
        if (bytesRead > 0){

            receivedMessage[bytesRead] = '\0';
            printf("%s\n", receivedMessage);

            sleep(1);

            bytesWritten = write(outFile_fd, MESSAGE, strlen(MESSAGE));
            if (bytesWritten == -1){
            
                printf("ERROR writing to file: %s\n", OUT_FIFO);
                return 3;
            }
        }
    }

    close(inFile_fd);
    close(outFile_fd);

    return 0; 
}