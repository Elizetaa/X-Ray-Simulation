#include "pacientes.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>


struct patient{
    int id;
    char *name;
    struct tm* timestamp;
};

struct queue_patient{
   QueueNodePatient *front; 
   QueueNodePatient *rear; 
};

struct queue_node_patient{
   Patient *info;        
   QueueNodePatient *next;   
};

Patient* create_patient(int id, const char *name, struct tm* timestamp){
    Patient* pont = (Patient*)malloc(sizeof(Patient));
    assert(pont != NULL || timestamp != NULL || name != NULL);

    pont->name = (char*)malloc(strlen(name) + 1); 
    strcpy(pont->name, name);

    pont->timestamp = (struct tm*)malloc(sizeof(struct tm)); 
    memcpy(pont->timestamp, timestamp, sizeof(struct tm));
    
    pont->id = id;

    return pont;
}

int get_patient_id(Patient* paciente){ 
    return paciente->id;
}

char* get_patient_name(Patient* paciente){ 
    return paciente->name;
}

struct tm* get_patient_timestamp(Patient *paciente){ 
    return paciente->timestamp;
}

void destroy_patient(Patient *paciente){ 
    free(paciente->name);
    free(paciente->timestamp);
    free(paciente);
}

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
   if (queue_is_empty_patient(queue)){ 
      queue->front = q;
   }
   else{ 
      queue->rear->next = q;
   }
   queue->rear = q;
}

Patient *queue_dequeue_patient(QueuePatient *queue){
   assert(!queue_is_empty_patient(queue));

   QueueNodePatient *temp = queue->front;
   Patient *data = temp->info;

   queue->front = queue->front->next;

   if (queue->front == NULL) {
      queue->rear = NULL;
   }

   free(temp);
   return data;
}

void queue_free_patient(QueuePatient *queue){
   QueueNodePatient *i = queue->front;
   while (i != NULL){
      QueueNodePatient *next = i->next;
      destroy_patient(i->info);  
      free(i);
      i = next;
   }
   free(queue);
}

void queue_print_patient(QueuePatient *queue){
   for (QueueNodePatient *i = queue->front; i != NULL; i = i->next)
      printf("Id: %d\n", i->info->id);
      usleep(500000);

      printf("\n");
}

void write_patient_in_file(Patient *paciente, FILE *paciente_file){
    char* nome = get_patient_name(paciente);
    struct tm *data_hora_atual = get_patient_timestamp(paciente);
    int ids = get_patient_id(paciente);
    int dia = data_hora_atual->tm_mday;
    int mes = data_hora_atual->tm_mon+1;
    int ano = data_hora_atual->tm_year +1900;
    fprintf(paciente_file, ("Id: %d Nome: %s HoraDeEntrada: %d/%d/%d\n\n"),ids,nome,dia,mes,ano);
}