#include "queue.h"
#include "pacientes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct queue_patient{
   QueueNodePatient *front; 
   QueueNodePatient *rear; 
};


struct queue_node_patient{
   Patient *info;        
   QueueNodePatient *next;   
};

QueuePatient *queue_create_patient(){
   QueuePatient *queue = (QueuePatient *)malloc(sizeof(QueuePatient));
   assert(queue != NULL);
   queue->front = queue->rear = NULL;
   return queue; 
}


int queue_is_empty_patient(QueuePatient *queue){
   return queue->front == NULL; 
}


void queue_enqueue_patient(QueuePatient *queue, Patient *data){
   QueueNodePatient *q = (QueueNodePatient *)malloc(sizeof(QueueNodePatient));
   assert(q != NULL);
   q->info = data;
   q->next = NULL;
   if (queue_is_empty(queue)){ 
      queue->front = q;
   }
   else{ 
      queue->rear->next = q;
   }
   queue->rear = q;
}


Patient *queue_dequeue_patient(QueuePatient *queue){
   assert(!queue_is_empty(queue));

   Patient *data = queue->front->info;

   if (queue->front != NULL)
      queue->front = queue->front->next;
   else
      queue->front = queue->rear = NULL;

   return data;
}


void queue_free_patient(QueuePatient *queue){
   for (QueueNodePatient *i = queue->front; i->next != NULL; i = i->next){
      QueueNodePatient *next = i->next;
      free(i);
      i = next;
   }
   free(queue->rear);
   free(queue);
}


void queue_print_patient(QueuePatient *queue){
   for (QueueNodePatient *i = queue->front; i != NULL; i = i->next)
      printf("%.2f", i->info);

   printf("\n");
}