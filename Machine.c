#include "exames.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "Pacientes.h"
#include "Machine.h"
#include <unistd.h>



struct queue_machine{ /* Nomeado como QueueMachine */
   QueueNodeMachine *front; 
   QueueNodeMachine *rear; 
};

struct queue_node_machine{ /* Nomeado como QueueNodeMachine */
   Machine *info;        
   QueueNodeMachine *next;   
};

struct XR_Machine{ /* nomeado como Machine */
   Patient *paciente;
   int machine_id;
   int timecount;
};

Machine* create_machine(Patient *paciente, int machine_id){ 
    Machine* machine = (Machine*)malloc(sizeof(Machine));
    assert(paciente != NULL || machine != NULL);
    machine->paciente = paciente;
    machine->timecount = 10;
    machine->machine_id = machine_id;
    return machine;
}

QueueMachine *queue_create_machine(){
   QueueMachine *queue = (QueueMachine *)malloc(sizeof(QueueMachine));
   assert(queue != NULL);
   queue->front = queue->rear = NULL;
   return queue; 
}


int queue_is_empty_machine(QueueMachine *queue){
   return queue->front == NULL; 
}


void queue_enqueue_machine(QueueMachine *queue, Machine *data){
   QueueNodeMachine *q = (QueueNodeMachine *)malloc(sizeof(QueueNodeMachine));
   assert(q != NULL);
   q->info = data;
   q->next = NULL;
   if (queue_is_empty_machine(queue)){ 
      queue->front = q;
   }
   else{ 
      queue->rear->next = q;
   }
   queue->rear = q;
}


Machine *queue_dequeue_machine(QueueMachine *queue){
   assert(!queue_is_empty_machine(queue));

   Machine *data = queue->front->info;

   if (queue->front != NULL)
      queue->front = queue->front->next;
   else
      queue->front = queue->rear = NULL;

   return data;
}

void queue_free_machine(QueueMachine *queue){
   for (QueueNodeMachine *i = queue->front; i->next != NULL; i = i->next){
      QueueNodeMachine *next = i->next;
      destroy_machine(i->info);
      free(i);
      i = next;
   }
   free(queue->rear);
   free(queue);
}

void queue_print_machine(QueueMachine *queue){
   if (queue->front == NULL){
      printf("Sem maquinas em andamento");
   }
   else{
      for (QueueNodeMachine *i = queue->front; i != NULL; i = i->next){
         printf("ID: %d, Maquina: %d Tempo na fila: %d" , get_patient_id(i->info->paciente), i->info->machine_id, i->info->timecount);
         printf("\n");
      }
   }
}

void destroy_machine(Machine *machine){
    destroy_patient(machine->paciente);
    free(machine);
}

int get_machine_timecount(Machine *machine){
    return machine->timecount;
}

Patient *get_machine_patient(Machine *machine){
    return machine->paciente;
}

int get_machine_id(Machine *machine){
    return machine->machine_id;
}

/*Caso haja um paciente na fila de espera, coloque ele em uma máquina e aloque ela na fila de máquinas*/
int manage_machine_slots(QueueMachine *machinequeue, int machine_slots, QueuePatient *patientqueue, int machine_id){
      if (queue_is_empty_patient(patientqueue)){
         return machine_slots;
      }
      if (machine_slots > 0){
         Patient *paciente = queue_dequeue_patient(patientqueue);
         Machine *maquina = create_machine(paciente, machine_id);
         queue_enqueue_machine(machinequeue, maquina);
         machine_slots -= 1;
         }
      return machine_slots;
}

/*Subtraia -1 de todos os elementos que já estão na fila de máquinas, caso a fila de máquinas esteja vazia não prossiga*/
void run_machine_queue(QueueMachine *machinequeue){
   if (!queue_is_empty_machine(machinequeue)){
      for (QueueNodeMachine *i = machinequeue->front; i != NULL; i = i->next){
         i->info->timecount -=1;
      }
   }
}

/*Função que verifica se o paciente deve sair da maquina*/
int is_timecount_zero(QueueMachine *maquina_queue) {
   return maquina_queue->front->info->timecount == 0;
}

void clear_terminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

