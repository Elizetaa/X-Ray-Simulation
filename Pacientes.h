#ifndef _PACIENTES_H
#define _PACIENTES_H
#include <time.h>
#include <stdio.h>

/*Definição das estruturas */
typedef struct patient Patient;
typedef struct queue_patient QueuePatient;
typedef struct queue_node_patient QueueNodePatient; 

/*Recebe o id de um paciente, o nome desse paciente, e um timestemp, e retorna um paciente com essas informações*/
Patient* create_patient(int id, const char *name, struct tm* timestamp); 

/*Retorna uma nova fila de pacientes*/
QueuePatient *queue_create_patient();

/*Recebe uma fila de pacientes e verifica se ela está vazia, retornando um valor booleano*/
int queue_is_empty_patient(QueuePatient *queue);

/*Recebe uma fila de pacientes e um paciente, e aloca este novo paciente no final da fila*/
void queue_enqueue_patient(QueuePatient *queue, Patient *data);

/*Recebe uma fila de pacientes, dealoca o paciente do começo da fila, e retorna este paciente*/
Patient *queue_dequeue_patient(QueuePatient *queue);

/*Recebe uma fila de pacientes, e libera a memoria alocada para ela*/
void queue_free_patient(QueuePatient *queue);

/*Recebe um paciente e retorna o ID dele*/
int get_patient_id(Patient* paciente); 

/*Recebe um paciente, e retorna o nome dele*/
char* get_patient_name(Patient* paciente); 

/*Recebe um paciente e retorna o timestemp desse paciente*/
struct tm* get_patient_timestamp(Patient *paciente); 

/*Recebe um paciente e libera a memoria alocada pra ele*/
void destroy_patient(Patient *paciente);

/*Recebe um paciente, um arquivo e a iteração do looping, e escreve as informações desse paciente nesse arquivo*/
void write_patient_in_file(Patient *paciente, FILE *paciente_file, int i);

/*Recebe uma fila de pacientes e retorna o numero de pacientes nela.*/
int get_n_patient_queue(QueuePatient *queue);
#endif