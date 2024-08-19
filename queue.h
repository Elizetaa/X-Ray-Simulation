#ifndef _QUEUE_H
#define _QUEUE_H
#include <time.h>

typedef struct queue_patient QueuePatient;
typedef struct queue_node_patient QueueNodePatient; 


QueuePatient *queue_create();


int queue_is_empty_patient(QueuePatient *queue);


void queue_enqueue_patient(QueuePatient *queue, float data);

float queue_dequeue_patient(QueuePatient *queue);

void queue_print_patient(QueuePatient *queue);


#endif
