#ifndef _MACHINE_H
#define _MACHINE_H

/*Definição das estruturas*/
typedef struct XR_Machine Machine;
typedef struct queue_machine QueueMachine;
typedef struct queue_node_machine QueueNodeMachine; 

/*Recebe um paciente e o ID deste paciente, e retorna uma máquina com essas informações*/
Machine* create_machine(Patient *paciente, int machine_id);

/*Retorna uma nova fila de máquinas*/
QueueMachine *queue_create_machine();

/*Recebe uma fila de máquinas, verifica se ela está vazia e retorna um valor booleano */
int queue_is_empty_machine(QueueMachine *queue);

/*Recebe uma fila de maquinas e uma maquina, e aloca esta maquina ao final desta fila*/
void queue_enqueue_machine(QueueMachine *queue, Machine *data);

/*Recebe uma fila de maquinas, retira o elemento na frente da fila e retorna a maquina removida*/
Machine *queue_dequeue_machine(QueueMachine *queue);

/*Recebe uma fila de maquinas e libera a memoria que pra ela foi alocada*/
void queue_free_machine(QueueMachine *queue);

/*Recebe uma maquina e libera a memória que pra ela foi alocada*/
void destroy_machine(Machine *machine);

/*Recebe uma maquina e retorna o paciente que está alocado nela*/
Patient *get_machine_patient(Machine *machine);

/*Recebe uma máquina e retorna o ID inteiro destá maquina*/
int get_machine_id(Machine *machine);

/*Recebe uma fila de maquinas, a quantidade de maquinas disponiveis, uma fila de pacientes e o ID de uma maquina, caso haja
uma maquina disponivel, aloca o primeiro paciente da fila de maquinas em uma dessas maquinas e retorna o numero de maquinas
disponiveis atualizado*/
int manage_machine_slots(QueueMachine *machinequeue, int machine_slots, QueuePatient *patientqueue, int machine_id);

/*Recebe uma fila de maquinas e atualiza o tempo que resta pra o fim do exame de todas as maquinas desta fila*/
void run_machine_queue(QueueMachine *machine);

/*Recebe uma fila de maquinas e retorna um valor booleano caso o exame tenha chegado ao fim*/
int is_timecount_zero(QueueMachine *maquina_queue);

/*Limpa o terminal*/
void clear_terminal(); 

#endif