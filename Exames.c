#include "exames.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "Pacientes.h"



struct Exame{

    int id;
    int rx_id;
    int patient_id;
    char *condition_IA;
    struct tm* timestamp;

};

struct queue_exam{
   QueueNodeExam *front; 
   QueueNodeExam *rear; 
};


struct queue_node_exam{
   Exam *info;        
   QueueNodeExam *next;   
};


Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time, const char *condition_IA){ 
    Exam* exame = (Exam*)malloc(sizeof(Exam));
    assert(exame != NULL || time != NULL || condition_IA != NULL);

    memcpy(exame->timestamp, time, sizeof(struct tm));

    strcpy(exame->condition_IA, condition_IA);

    if (exame == NULL || exame->timestamp == NULL || exame->condition_IA == NULL)
        return NULL;

    exame->id = id;
    exame->patient_id = patient_id;
    exame->rx_id = rx_id;
    return exame;
}

QueueExam *queue_create_exam(){
   QueueExam *queue = (QueueExam *)malloc(sizeof(QueueExam));
   assert(queue != NULL);
   queue->front = queue->rear = NULL;
   return queue; 
}


int queue_is_empty_exam(QueueExam *queue){
   return queue->front == NULL; 
}


void queue_enqueue_exam(QueueExam *queue, Exam *data){
   QueueNodeExam *q = (QueueNodeExam *)malloc(sizeof(QueueNodeExam));
   assert(q != NULL);
   q->info = data;
   q->next = NULL;
   if (queue_is_empty_exam(queue)){ 
      queue->front = q;
   }
   else{ 
      queue->rear->next = q;
   }
   queue->rear = q;
}


Exam *queue_dequeue_exam(QueueExam *queue){
   assert(!queue_is_empty_exam(queue));

   Exam *data = queue->front->info;

   if (queue->front != NULL)
      queue->front = queue->front->next;
   else
      queue->front = queue->rear = NULL;

   return data;
}


void queue_free_exam(QueueExam *queue){
   for (QueueNodeExam *i = queue->front; i->next != NULL; i = i->next){
      QueueNodeExam *next = i->next;
      free(i);
      i = next;
   }
   free(queue->rear);
   free(queue);
}


void queue_print_exam(QueueExam *queue){
   for (QueueNodeExam *i = queue->front; i != NULL; i = i->next)
      printf("%d", i->info->id);

      printf("\n");
}

void destroy_exam(Exam *exame){
    free(exame->condition_IA);
    free(exame);
}

int get_exam_id(Exam *exame){
    return exame->id;
}

int get_exam_patient_id(Exam *exame){
    return exame->patient_id;
}

int get_exam_rx_id(Exam *exame){
    return exame->rx_id;
}

struct tm* get_exam_time(Exam *exame){
    return exame->timestamp;
}
