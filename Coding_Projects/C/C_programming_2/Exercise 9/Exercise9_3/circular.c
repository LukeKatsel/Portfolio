#include <stdio.h>

#include "circular.h"


void CircularInitialize(CircularQueue * q){

   q->head = 0;
   q->tail = 0;
   q->itemCount = 0;

}
void CircularEnqueue(CircularQueue * q, int value){
   
   q->items[q->head] = value;                         // Store the value in the head index
   q->head = (q->head + 1) % QUEUE_SIZE;              // Move the head to the next position

   if (q->itemCount < QUEUE_SIZE) {
      q->itemCount++;                                 // Increase the item count until the queue is full
   } 
   else {
      q->tail = (q->tail + 1) % QUEUE_SIZE;           // Move the tail to the next position, effectively overwriting the oldest value
   }
}

int CircularDequeue(CircularQueue * q, int *pValue){

   if (q->itemCount > 0){

      *pValue = q->items[q->tail];
      q->tail = (q->tail + 1) %  QUEUE_SIZE;
      q->itemCount--;
      return 1;
   }
   return 0;
}