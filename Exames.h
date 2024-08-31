#ifndef _EXAMES_H
#define _EXAMES_H
#include <stdio.h>
#include <time.h>

/*Estruturas utilizadas*/

typedef struct Exame Exam;
typedef struct queue_exam QueueExam;
typedef struct queue_node_exam QueueNodeExam; 
typedef struct report Report;

/*Cria e retorna uma nova fila de exames*/
QueueExam *queue_create_exam();

/*Recebe um exame, o ID do exame e retorna um laudo*/
Report *create_report(Exam *exame, int id);

/*Recebe um arquivo, um laudo, e a iteração atual do looping e escreve as informações de um laudo em um arquivo*/
void write_report_in_file(FILE* report_file, Report* report, int i);

/*Recebe uma fila de exames. checa se está vazia, e retorna um valor booleano*/
int queue_is_empty_exam(QueueExam *queue);

/*Recebe uma fila de exames, e libera a memória alocada para ela*/
void queue_free_exam(QueueExam *queue);

/*Recebe uma fila de exames e um Exame, e adiciona este exame na fila de exames.*/
void queue_enqueue_exam(QueueExam *queue, Exam *data);

/*Recebe uma fila de exames, e retorna o primeiro elemento desta fila de exames*/
Exam *queue_dequeue_exam(QueueExam *queue);

/*Recebe um ID do exame, o ID de um paciente, o ID da máquina de raio-x, um timestamp, a codinção deste paciente
e sua prioridade, e retorna um exame com estas informações*/
Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time, char *condition_IA, int prio); 

/*Recebe um exame, e retorna o ID deste exame*/
int get_exam_id(Exam *exame); 

/*Recebe um exame, e retorna o ID do paciente deste exame*/
int get_exam_patient_id(Exam *exame); 

/*Recebe um exame, e retorna o ID da maquina de raio-x deste exame*/
int get_exam_rx_id(Exam *exame); 

/*Recebe um exame, e retorna o tempo de espera por laudo deste exame*/
int get_time_report(Exam *aux_exam_2);

/*Recebe um exame, e retorna o timestemp deste exame*/
struct tm* get_exam_time(Exam *exame); 

/*Recebe um exame, e retorna a condição deste exame*/
char *get_exam_condition(Exam *exame);

/*Recebe um exame, e retorna a prioridade deste exame*/
int get_exam_prio(Exam* exame);

/*Retorna um novo diagnostico, gerado aleatoriamente por uma semi-IA*/
char *create_diagnosis();

/*Recebe um diagnostico, e retorna o grau de prioridade deste diagnostico*/
int get_diagnostico_prio(char *diagnostico);

/*Recebe um exame e um arquivo, e escreve as informações deste exame neste arquivo*/
void write_exam_in_file(Exam *exam, FILE *file, int i);

/*Recebe um exame e uma fila de prioridade de exames, e adiciona este exame nesta fila de maneira prioritaria*/
void enqueue_priority(Exam *exame, QueueExam *priority_queue);

/*Recebe uma fila de prioridades, e atualiza o tempo de aguardo por laudo desta fila de prioridades*/
void time_report_update(QueueExam *exam_priority_queue);

#endif