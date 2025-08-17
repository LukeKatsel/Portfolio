#include <stdio.h>

#include "circular.h"

#define FILENAME "data.txt"
#define LINE_SIZE 128

int main()
{ 
    int i,j;
    int number;
    CircularQueue my_queue;

    CircularInitialize(&my_queue);

    // Add 7, remove 7
    for (i=0; i < 100; ++i)
    {   
        for(j=0; j < 7; j++)
        {
            CircularEnqueue(&my_queue, j);
        }

        for(j=0; j < 7; j++)
        {
            CircularDequeue(&my_queue, &number);
            if (number != j)
            {
                printf("Failed validation test 100x7.  Expected %d, dequeued %d\n", j, number);
            }
        }
    }

    // Add 7, remove 5
    for (i=0; i < 50; ++i)
    {   
        for(j=0; j < 7; j++)
        {
            CircularEnqueue(&my_queue, j);
        }

        for(j=0; j < 5; j++)
        {
            CircularDequeue(&my_queue, &number);

            if (number != (((i * 5) + j) % 7))
            {
                // if this happens before we have a full list, then it's an error
                if (i * 2 + 7 < QUEUE_SIZE)
                {
                    printf("ERROR: ");
                }
                printf("%d: Value mismatch test 50x7 with count %d.  Expected %d, dequeued %d\n", i, my_queue.itemCount,
                                                                                         (((i * 5) +j) % 7), number);
            }
        }
    }

    return 0;
}
