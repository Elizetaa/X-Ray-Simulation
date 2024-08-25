#ifndef _MACHINE_H
#define _MACHINE_H

/*Definição das estruturas*/
typedef struct XR_Machine Machine;
typedef struct queue_machine QueueMachine;
typedef struct queue_node_machine QueueNodeMachine; 

/*Aloca um paciente em uma máquina*/
Machine* create_machine(Patient *paciente, int machine_id);

/*Cria uma nova fila de máquinas*/
QueueMachine *queue_create_machine();

/*Verifica se a fila de máquinas está vazia*/
int queue_is_empty_machine(QueueMachine *queue);

/*Aloca uma máquina em uma fila de máquinas*/
void queue_enqueue_machine(QueueMachine *queue, Machine *data);

/*Desenfilera um elemento de uma fila de máquinas*/
Machine *queue_dequeue_machine(QueueMachine *queue);

/*Libera memoria de uma fila de maquinas*/
void queue_free_machine(QueueMachine *queue);

/*Imprime os elementos de uma fila de máquinas*/
void queue_print_machine(QueueMachine *queue);

/*Libera memória de uma unica máquina*/
void destroy_machine(Machine *machine);

/*Recolhe o tempo de realização do exame*/
int get_machine_timecount(Machine *machine);

/*Recolhe o paciente que está dentro da maquina*/
Patient *get_machine_patient(Machine *machine);

/*Recolhe o ID da maquina*/
int get_machine_id(Machine *machine);

/*Gerencia o funcionamento da máquina*/
int manage_machine_slots(QueueMachine *machinequeue, int machine_slots, QueuePatient *patientqueue, int machine_id);

/*Percorre o andamento dos exames*/
void run_machine_queue(QueueMachine *machine);

/*Verifica se o tempo de realização do exame chegou ao fim*/
int is_timecount_zero(QueueMachine *maquina_queue);

/*Limpa o terminal*/
void clear_terminal(); 

#endif