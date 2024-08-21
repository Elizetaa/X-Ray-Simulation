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

int XRMachineManager (int machine_slots, QueueMachine *machine_queue, QueueExam * exam_queue, QueuePatient *patient_queue, int machine_id, int exam_id){
    assert(patient_queue != NULL && exam_queue != NULL && machine_queue != NULL);
    Patient *patient;
    if (queue_is_empty_patient(patient_queue)){
        return machine_slots;
    }
    run_machine_queue(machine_queue, exam_queue, exam_id);
    if (machine_slots == 0){
        return machine_slots;
    }   
    else{
        patient = queue_dequeue_patient(patient_queue);
        Machine *machine = create_machine(patient, machine_id);
        queue_enqueue_machine(machine_queue, machine);
        return machine_slots -1;
    }
} 

void run_machine_queue(QueueMachine *queue, QueueExam *exam_queue, int exam_id){
   if(!queue_is_empty_machine(queue)){
      return;
   };
   int condition;
   int it_aux;
   if(queue->front){
      return;
   }
   for(QueueNodeMachine *i = queue->front; i->next !=NULL; i = i->next){
      i->info->timecount --;
      if(i->info->timecount == 0){
         condition = rand()%100;
         if (condition<30){
           Exam *exam = create_exam(exam_id, get_patient_id(i->info->paciente), i->info->machine_id, get_patient_timestamp(i->info->paciente), "Saude Normal", 1);
           queue_enqueue_exam(exam_queue, exam);
            it_aux = 1;

         }
         if(condition>=30 && condition <50){
            Exam *exam = create_exam(exam_id, get_patient_id(i->info->paciente), i->info->machine_id, get_patient_timestamp(i->info->paciente), "Bronquite", 2);
            queue_enqueue_exam(exam_queue, exam);  
            it_aux = 1;

         }
         if(condition>=50 && condition <60){
            Exam *exam = create_exam(exam_id, get_patient_id(i->info->paciente), i->info->machine_id, get_patient_timestamp(i->info->paciente), "Pneumonia", 3);
            queue_enqueue_exam(exam_queue, exam);  
            it_aux = 1;

         }
         if(condition>=60 && condition <70){
            Exam *exam = create_exam(exam_id, get_patient_id(i->info->paciente), i->info->machine_id, get_patient_timestamp(i->info->paciente), "Covid", 4);
            queue_enqueue_exam(exam_queue, exam);  
            it_aux = 1;

         }
         if(condition>=70 && condition <75){
            Exam *exam = create_exam(exam_id, get_patient_id(i->info->paciente), i->info->machine_id, get_patient_timestamp(i->info->paciente), "Embolia Pulmonar", 4);
            queue_enqueue_exam(exam_queue, exam);  
            it_aux = 1;

         }
         if(condition>=75 && condition <80){
            Exam *exam = create_exam(exam_id, get_patient_id(i->info->paciente), i->info->machine_id, get_patient_timestamp(i->info->paciente), "Derrame Pleural", 4);
            queue_enqueue_exam(exam_queue, exam);  
            it_aux = 1;

         }
         if(condition>=80 && condition <85){
            Exam *exam = create_exam(exam_id, get_patient_id(i->info->paciente), i->info->machine_id, get_patient_timestamp(i->info->paciente), "Fibrose Pulmonar", 5);
            queue_enqueue_exam(exam_queue, exam);  
            it_aux = 1;

         }
         if(condition>=85 && condition <90){
            Exam *exam = create_exam(exam_id, get_patient_id(i->info->paciente), i->info->machine_id, get_patient_timestamp(i->info->paciente), "Tuberculose", 5);
            queue_enqueue_exam(exam_queue, exam); 
            it_aux = 1;

         }
         if(condition>=90 && condition <100){
            Exam *exam = create_exam(exam_id, get_patient_id(i->info->paciente), i->info->machine_id, get_patient_timestamp(i->info->paciente), "Câncer de pulmão", 6);
            queue_enqueue_exam(exam_queue, exam);  
            it_aux = 1;
         }
      }
      if(it_aux == 1){
         queue_dequeue_machine(queue);
      }
   }
}