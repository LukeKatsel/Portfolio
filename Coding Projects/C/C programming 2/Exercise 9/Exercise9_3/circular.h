#ifndef CIRCULAR_H
#define CIRCULAR_H

#define QUEUE_SIZE 100

typedef struct {
    int head;
    int tail; 
    int itemCount;
    int items[QUEUE_SIZE];
} CircularQueue;

void CircularInitialize(CircularQueue * q);
void CircularEnqueue(CircularQueue * q, int value);
int CircularDequeue(CircularQueue * q, int *pValue);

#endif