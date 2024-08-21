#include "queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "pacientes.h"

struct queue
{
   QueueNode *front; 
   QueueNode *rear;  
};


struct queue_node
{
   Patient info; 
   QueueNode *next; 
};

Queue *q_create()
{
   Queue *q = (Queue *)malloc(sizeof(Queue)); 
   q->front = q->rear = NULL;            
   return q;
}

int q_is_empty(Queue *q)
{
   return q->front == NULL;
}

void q_enqueue(Queue *q, Patient *v)
{
   QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode)); 
   node->info = *v;
   node->next = NULL;

   if (q_is_empty(q))
      q->front = node;
   else
      q->rear->next = node;

   q->rear = node;
}

Patient q_dequeue(Queue *q)
{
   Patient v = q->front->info;
   QueueNode *p = q->front; 

   assert(!q_is_empty(q));


   if (q->front != q->rear)
      q->front = q->front->next;
   else
      q->front = q->rear = NULL;

   free(p);
   return v;
}

void q_free(Queue *q)
{
   QueueNode *p = q->front;
   while (p != NULL)
   {
      QueueNode *t = p->next; 
      free(p);             
      p = t;                
   }
   free(q); 
}

void q_print(Queue *q)
{
   for (QueueNode *p = q->front; p != NULL; p = p->next)
      printf("%.2f ", p->info);

   printf("\n");
}
