#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "pacientes.h"
#include "exames.h"
#include "Machine.h"
#include <unistd.h>
#include <string.h>


struct Exame{

    int id;
    int rx_id;
    int patient_id;
    char *condition_IA;
    struct tm* timestamp;
    int prio;
    int report;
};

struct queue_exam{
   QueueNodeExam *front; 
   QueueNodeExam *rear; 
};


struct queue_node_exam{
   Exam *info;        
   QueueNodeExam *next;   
};

struct report{
   int id;
   int exam_id;
   char *condition;
   struct tm *timestamp;
   int time;

};

Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time, char *condition_IA, int prio){ 
   Exam* exame = (Exam*)malloc(sizeof(Exam));
   assert(exame != NULL || time != NULL || condition_IA != NULL);
   if (time == NULL || condition_IA == NULL) {
        free(exame);
        return NULL;
    }
    exame->id = id;
    exame->patient_id = patient_id;
    exame->rx_id = rx_id;
    exame->timestamp = time;
    exame->condition_IA = (char *)malloc(sizeof(char) * strlen(condition_IA));
    strcpy(exame->condition_IA, condition_IA);
    exame->prio = prio;
    exame->report = 30;
    return exame;
}

Report *create_report(Exam *exame, int id){
   Report* report = (Report*)malloc(sizeof(Report));
   assert(report != NULL);
   struct tm* data_hora_atual;
   time_t segundos;
   time(&segundos);
   int p = rand()%100;
   char *a;
   report->time = 0;
   if (p < 80){
      report->condition = exame->condition_IA;
   }
   else{
      a = create_diagnosis();
      while(exame->condition_IA == a){
         a = create_diagnosis();
      }
      report->condition = a;
   }
   data_hora_atual = localtime(&segundos);
   report->id = id;
   report->exam_id = exame->id;
   report->timestamp = data_hora_atual;
   return report;
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

int get_time_report(Exam *aux_exam_2){
   return aux_exam_2->report;
}

void queue_free_exam(QueueExam *queue) {
    QueueNodeExam *noatual = queue->front;
    while (noatual != NULL) {
        QueueNodeExam *next = noatual->next;
        free(noatual);
        noatual = next;
    }
    free(queue); 
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

char *get_exam_condition(Exam *exame){
   return exame->condition_IA;
}

int get_exam_prio(Exam* exame){
   return exame->prio;
}

char *create_diagnosis(){
   int diagnosis = rand() % 100;
   if (diagnosis < 30){
      return "Saude Normal";
   }
   else if (diagnosis >= 30 && diagnosis < 50){
      return "Bronquite";
   }
   else if (diagnosis >= 50 && diagnosis < 60){
      return "Pneumonia";
   }
   else if (diagnosis >= 60 && diagnosis < 70){
      return "COVID";
   }
   else if (diagnosis >= 70 && diagnosis < 75){
      return "Embolia pulmonar";
   }
   else if (diagnosis >= 75 && diagnosis < 80){
      return "Derrame pleural";
   }
   else if (diagnosis >= 80 && diagnosis < 85){
      return "Fibrose pulmonar";
   }
   else if (diagnosis >= 85 && diagnosis < 90){
      return "Tuberculose";
   }
   else {
      return "Cancer de pulmao";
   }
}

int get_diagnostico_prio(char *diagnostico){
   if (!strcmp(diagnostico, "Saude Normal")){
      return 1;
   }
   else if(!strcmp(diagnostico, "Bronquite")){
      return 2;
   }
   else if(!strcmp(diagnostico, "Pneumonia")){
      return 3;
   }
   else if(!strcmp(diagnostico, "COVID")){
      return 4;
   }
   else if(!strcmp(diagnostico, "Embolia pulmonar")){
      return 4;
   }
   else if(!strcmp(diagnostico, "Derrame pleural")){
      return 4;
   }
   else if(!strcmp(diagnostico, "Fibrose pulmonar")){
      return 5;
   }
   else if(!strcmp(diagnostico, "Tuberculose")){
      return 5;
   }
   else if(!strcmp(diagnostico, "Cancer de pulmao")){
      return 6;
   }
   else {
      return 0;
   }
}

void write_exam_in_file(Exam *exam, FILE *file){
   char* condition = get_exam_condition(exam);
   struct tm *data_hora_atual = get_exam_time(exam);
   int patient_id = get_exam_patient_id(exam);
   int machine_id = get_exam_rx_id(exam);
   int exam_id = get_exam_id(exam);
   int prio = get_exam_prio(exam);
   int dia = data_hora_atual->tm_mday;
   int mes = data_hora_atual->tm_mon+1;
   int ano = data_hora_atual->tm_year +1900;
   fprintf(file, ("ID do Exame: %d, Maquina Utilizada: %d, ID do Paciente: %d, Condicao: %s, Prioridade: %d, HoraDeEntrada: %d/%d/%d\n"), exam_id, machine_id, patient_id, condition,prio,dia,mes,ano);
}

void enqueue_priority(Exam *exame, QueueExam *priority_queue){
   QueueNodeExam *node = (QueueNodeExam*)malloc(sizeof(QueueNodeExam));
   node->info = exame;
   node->next = NULL;
   if (priority_queue->front == NULL || priority_queue->front->info->prio < exame->prio){
      node->next = priority_queue->front;
      priority_queue->front = node;
      
   }
   else{
      QueueNodeExam *aux_node = priority_queue->front;
      while (aux_node->next != NULL && aux_node->next->info->prio >= exame->prio){
         aux_node = aux_node->next;
      }
      node->next = aux_node->next;
      aux_node->next = node;
      if (node->next == NULL) {
            priority_queue->rear = node;
      }
   }
}


void write_report_in_file(FILE* report_file, Report* report){
   int hours = report->timestamp->tm_hour;
   int minutes = report->timestamp->tm_min;
   int seconds = report->timestamp->tm_sec;
   fprintf(report_file,("ID: %d, Exam_ID: %d, Codition: %s, Timestamp: %d:%d:%d\n"), report->id,report->exam_id,report->condition,hours,minutes,seconds);
}

void time_report_update(QueueExam *exam_priority_queue){
   for (QueueNodeExam *i = exam_priority_queue->front; i != NULL; i = i->next){
      i->info->report++;      
   }
}
