#ifndef _PACIENTES_H
#define _PACIENTES_H
#include <time.h>
#include <stdio.h>


typedef struct patient Patient;
typedef struct queue_patient QueuePatient;
typedef struct queue_node_patient QueueNodePatient; 

Patient* create_patient(int id, const char *name, struct tm* timestamp); 

QueuePatient *queue_create_patient();

int queue_is_empty_patient(QueuePatient *queue);

void queue_enqueue_patient(QueuePatient *queue, Patient *data);

Patient *queue_dequeue_patient(QueuePatient *queue);

void queue_print_patient(QueuePatient *queue);

int get_patient_id(Patient* paciente); 

char* get_patient_name(Patient* paciente); 

struct tm* get_patient_timestamp(Patient *paciente); 

void destroy_patient(Patient *paciente);

void write_patient_in_file(Patient *paciente, FILE *paciente_file);

#endif