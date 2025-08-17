#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define WORDS_FILENAME "text.txt"
#define MAX_WORD_LENGTH 50
#define MAX_NUM_WORDS 100
#define FIFO_NAME "shared_fifo"

void *FunctionRead(void *){                         // function to read txt file and write to fifo 

    FILE *fileptr = fopen(WORDS_FILENAME, "r");     // open file
    if (fileptr == NULL){

        perror("opening file error");               // error checking
        return NULL;
    }

    char words[MAX_NUM_WORDS][MAX_WORD_LENGTH];     // array creation
    int wordCount = 0;

    while ((wordCount < MAX_NUM_WORDS) && (fscanf(fileptr, "%s", words[wordCount]) == 1)){

        wordCount++;                                // load words into array and count words
    }

    fclose(fileptr);                                // done with file so close

    int fifo_fd = open(FIFO_NAME, O_WRONLY);        // open fifo for writing
    if (fifo_fd == -1){

        perror("fifo opening error");               // error checking
        pthread_exit(NULL);
    }

    int i;

    while (1){

        for (i = 0; i < wordCount; i++){            // write words from array to fifo

            write(fifo_fd, words[i], MAX_WORD_LENGTH);  
            sleep(1);
        }
    }

    close(fifo_fd);                                 // done with fifo so close

    return NULL;
}

void *FunctionPrint(void *){                        // function to print words from fifo

    int fifo_fd = open(FIFO_NAME, O_RDONLY);        // open fifo
    if (fifo_fd == -1){

        perror("fifo opening error");               // error checking
        pthread_exit(NULL);
    }

    char word[MAX_WORD_LENGTH];

    while (1){

        if (read(fifo_fd, word, MAX_WORD_LENGTH)){  // read from fifo

            printf("%s\n", word);                   // print each word
        }
    }

    close(fifo_fd);                                 // done with fifo so close

    return NULL;
}

int main(void){

    while (mkfifo(FIFO_NAME, 0666) == -1){          // create fifo 
        
        unlink(FIFO_NAME);                          // if exists already, delete and try again
    }

    pthread_t threadRead;                           // create threads objects
    pthread_t threadPrint;
    pthread_attr_t attr;

    pthread_attr_init(&attr);                       // set attributes

    pthread_create(&threadRead, &attr, &FunctionRead, NULL);
    pthread_create(&threadPrint, &attr, &FunctionPrint, NULL);  // create threads

    pthread_join(threadRead, NULL);                 // don't end main before threads are done
    pthread_join(threadPrint, NULL);

    unlink(FIFO_NAME);                              // delete fifo, but will never occur unless error

    return 0;
}