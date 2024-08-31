#include "exames.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "Pacientes.h"
#include "Machine.h"
#include <unistd.h>



struct queue_machine{ 
   QueueNodeMachine *front; 
   QueueNodeMachine *rear; 
};

struct queue_node_machine{ 
   Machine *info;        
   QueueNodeMachine *next;   
};

struct XR_Machine{
   Patient *paciente;
   int machine_id;
   int timecount;
};

Machine* create_machine(Patient *paciente, int machine_id){ 
    Machine* machine = (Machine*)malloc(sizeof(Machine));
    assert(paciente != NULL || machine != NULL);
    machine->paciente = paciente;
    machine->timecount = 11;
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

void queue_free_machine(QueueMachine *queue) {
    QueueNodeMachine *noatual = queue->front;
    while (noatual != NULL) {
        QueueNodeMachine *next = noatual->next;
        destroy_machine(noatual->info);
        free(noatual);
        noatual = next;
    }
    free(queue);
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

void run_machine_queue(QueueMachine *machinequeue){
   if (!queue_is_empty_machine(machinequeue)){
      for (QueueNodeMachine *i = machinequeue->front; i != NULL; i = i->next){
         i->info->timecount -=1;
      }
   }
}

int is_timecount_zero(QueueMachine *maquina_queue) {
   return maquina_queue->front->info->timecount == 0;
}

void clear_terminal() {
   system("clear");
}

