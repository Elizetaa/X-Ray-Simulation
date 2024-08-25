#ifndef _EXAMES_H
#define _EXAMES_H
#include <stdio.h>
#include <time.h>

typedef struct Exame Exam;
typedef struct queue_exam QueueExam;
typedef struct queue_node_exam QueueNodeExam; 
typedef struct report Report;

/*Cria uma nova fila de exames*/
QueueExam *queue_create_exam();

/*Cria um laudo*/
Report *create_report(Exam *exame, int id);

/*Destroi um laudo */
void destroy_report(Report *report);

/*Imprime as informações de um laudo*/
void print_file_report(Report *report);

/*Escreve as informações de um laudo em um arquivo*/
void write_report_in_file(FILE* report_file, Report* report);

/*Checa se uma fila de exames está vazia*/
int queue_is_empty_exam(QueueExam *queue);

/*Libera memória de uma fila de exames*/
void queue_free_exam(QueueExam *queue);

/*Adiciona um novo Exam em uma fila de exames*/
void queue_enqueue_exam(QueueExam *queue, Exam *data);

/*Remove o primeiro elemento da fila de uma fila de exames*/
Exam *queue_dequeue_exam(QueueExam *queue);

/*Imprime os exames de uma fila de exames*/
void queue_print_exam(QueueExam *queue);

/*Cria um novo Exame*/
Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time, char *condition_IA, int prio); 

/*Limpa a memória de um exame*/
void destroy_exam(Exam *exame); 

/*Coleta o ID de um exame*/
int get_exam_id(Exam *exame); 

/*Coleta o ID de um paciente no primeiro exame da fila*/
int get_exam_patient_id(Exam *exame); 

/*Coleta o ID de raio x de um exame*/
int get_exam_rx_id(Exam *exame); 

/*Coleta o tempo restante de laudo*/
int get_time_report(Exam *aux_exam_2);

/*Coleta o timestemp de um exame*/
struct tm* get_exam_time(Exam *exame); 

/*Coleta a condição de um exame*/
char *get_exam_condition(Exam *exame);

/*Coleta a prioridade de um exame*/
int get_exam_prio(Exam* exame);

/*Cria um novo diagnostico*/
char *create_diagnosis();

/*Gera a prioridade de um diagnostico*/
int get_diagnostico_prio(char *diagnostico);

/*Escreve um exame em um arquivo*/
void write_exam_in_file(Exam *exam, FILE *file);

/*Enfilera um exame numa fila de prioridades*/
void enqueue_priority(Exam *exame, QueueExam *priority_queue);

/*Atualiza o tempo em aguardo do laudo*/
void time_report_update(QueueExam *exam_priority_queue);

#endif