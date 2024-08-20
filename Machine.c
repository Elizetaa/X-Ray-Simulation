#include "exames.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "Pacientes.h"
#include "Machine.h"


struct XR_Machine{ /* nomeado como Machine */
   Patient *paciente;
   int timecount;
};
struct queue_machine{ /* Nomeado como QueueMachine */
   QueueNodeMachine *front; 
   QueueNodeMachine *rear; 
};

struct queue_node_machine{ /* Nomeado como QueueNodeMachine */
   Machine *info;        
   QueueNodeMachine *next;   
};

Machine* create_machine(Patient *paciente, int *timecount){ 
    Machine* machine = (Machine*)malloc(sizeof(Machine));
    assert(paciente != NULL || machine != NULL || timecount != NULL);
   /* Do jeito que está SEMPRE vai retornar NULL
    if (machine == NULL || machine->paciente == NULL || machine->timecount == NULL)
        return NULL;
   */
    machine->paciente = paciente;
    machine->timecount = 10; /* Você não está usando a variavel timecount que a função pede */
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
      free(i);
      i = next;
   }
   free(queue->rear);
   free(queue);
}

/*
void queue_print_machine(QueueMachine *queue){
   for (QueueNodeMachine *i = queue->front; i != NULL; i = i->next)
      queue_print_patient(i->info->paciente);

   printf("\n");
}
*/
void destroy_machine(Machine *machine){
    destroy_patient(machine->paciente); /* Mudei essa parte */
    free(machine);
}

int get_machine_timecount(Machine *machine){
    return machine->timecount;
}

Patient *get_machine_patient(Machine *machine){
    return machine->paciente;
}

