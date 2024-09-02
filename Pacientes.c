#include "Pacientes.h"
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
   QueueNodePatient *noatual = queue->front;
   while (noatual != NULL){
      QueueNodePatient *next = noatual->next;
      destroy_patient(noatual->info);  
      free(noatual);
      noatual = next;
   }
   free(queue);
}

void queue_print_patient(QueuePatient *queue){
   if (queue->front == NULL){
      printf ("Nao ha pacientes em aguardo");
   }
   else{
      for (QueueNodePatient *i = queue->front; i != NULL; i = i->next){
         printf("Id do paciente: %d\n", i->info->id);
         printf("\n");
      }
   }
}

void write_patient_in_file(Patient *paciente, FILE *paciente_file, int i){
    char* nome = get_patient_name(paciente);
    struct tm *data_hora_atual = get_patient_timestamp(paciente);
    int ids = get_patient_id(paciente);
    int dia = data_hora_atual->tm_mday;
    int mes = data_hora_atual->tm_mon+1;
    int ano = data_hora_atual->tm_year +1900;
    int hora = data_hora_atual->tm_hour;
    int min = data_hora_atual->tm_min;
    int seg = data_hora_atual->tm_sec;
    fprintf(paciente_file, ("Id: %d, Nome: %s, Hora de entrada: %d:%d:%d, Data: %d/%d/%d, Iteração: %d\n"),ids, nome, hora, min, seg, dia, mes, ano, i);
}

int get_n_patient_queue(QueuePatient *queue){
   int cont = 0;
   for(QueueNodePatient *i = queue->front; i != NULL; i = i->next){
      cont++;
   }
   return cont;
}
