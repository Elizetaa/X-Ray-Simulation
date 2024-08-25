#ifndef _PACIENTES_H
#define _PACIENTES_H
#include <time.h>
#include <stdio.h>

/*Definição das estruturas */
typedef struct patient Patient;
typedef struct queue_patient QueuePatient;
typedef struct queue_node_patient QueueNodePatient; 

/*Cria um novo paciente*/
Patient* create_patient(int id, const char *name, struct tm* timestamp); 

/*Cria uma nova fila de pacientes*/
QueuePatient *queue_create_patient();

/*Verifica se uma fila de pacientes está vazia*/
int queue_is_empty_patient(QueuePatient *queue);

/*Enfilera um novo paciente em uma fila de pacientes*/
void queue_enqueue_patient(QueuePatient *queue, Patient *data);

/*Desenfilera um paciente de uma fila de pacientes*/
Patient *queue_dequeue_patient(QueuePatient *queue);

/*Libera memoria de uma fia de pacientes*/
void queue_free_patient(QueuePatient *queue);

/*Recolhe o ID de um paciente*/
int get_patient_id(Patient* paciente); 

/*Recolhe o nome de um paciente*/
char* get_patient_name(Patient* paciente); 

/*Recolhe o timestemp de um paciente*/
struct tm* get_patient_timestamp(Patient *paciente); 

/*Destroi um paciente*/
void destroy_patient(Patient *paciente);

/*Escreve as informações de um paciente em um arquivo*/
void write_patient_in_file(Patient *paciente, FILE *paciente_file, int i);

/*Recolhe o numero de pacientes em uma fila*/
int get_n_patient_queue(QueuePatient *queue);
#endif