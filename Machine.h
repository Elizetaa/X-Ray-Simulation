#ifndef _MACHINE_H
#define _MACHINE_H

typedef struct XR_Machine Machine;

typedef struct queue_machine QueueMachine;

typedef struct queue_node_machine QueueNodeMachine; 

Machine* create_machine(Patient *paciente, int machine_id);

QueueMachine *queue_create_machine();

int queue_is_empty_machine(QueueMachine *queue);

void queue_enqueue_machine(QueueMachine *queue, Machine *data);

Machine *queue_dequeue_machine(QueueMachine *queue);

void queue_free_machine(QueueMachine *queue);
/*
void queue_print_machine(QueueMachine *queue); Mal feito
*/
void destroy_machine(Machine *machine);

int get_machine_timecount(Machine *machine);

Patient *get_machine_patient(Machine *machine);

#endif