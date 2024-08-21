#ifndef _QUEUE_H
#define _QUEUE_H
#include "Pacientes.h"

typedef struct queue Queue;         
typedef struct queue_node QueueNode; 

Queue *q_create();

int q_is_empty(Queue *q);

void q_enqueue(Queue *q, Patient *x);

Patient q_dequeue(Queue *q);

void q_free(Queue *q);

void q_print(Queue *q);

#endif
