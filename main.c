#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "pacientes.h"
#include "exames.h"
#include "Machine.h"
#include <unistd.h>





int main()
{   
    
    /*Declaração de variaveis e structs de tempo*/
    int ids = 1;
    struct tm* data_hora_atual;
    time_t segundos;
    
    /*Define as variaveis das máquinas*/
    int machine_slots = 5;
    int machine_id = 1;

    /*Define as variaveis de exame*/
    int exam_id = 1;
    /*Abertura do arquivo na variável patient_file*/
    FILE *patient_file = fopen("db_patient.txt", "a+");
    
    /*Definição da seed como nula para criar númeroa aleatórios*/
    srand(time(NULL));
    
    /*Criação de uma fila para as máquinas ocupadas*/
    QueueMachine *machine_queue = queue_create_machine();

    /*Criação da fila de pacientes*/
    QueuePatient *patient_queue = queue_create_patient();
    
    /*Criação da fila de exames*/
    QueueExam *exam_queue = queue_create_exam();

    
    /*Looping principal, contem a contagem do tempo em "unidades de tempo" e realiza as operações*/
    for (int i = 1; i <= 200; i++){
       /*Verifica uma condição de 20% de chance de um paciente entrar*/
       if  (rand()%5 == 0){
            
            /* Adiciona o paciente dentro do arquivo patient_file.txt*/
            time(&segundos);
            data_hora_atual = localtime(&segundos);
            Patient *paciente = create_patient(ids, "nomegenerico", data_hora_atual);
            write_patient_in_file(paciente, patient_file);

            /*Adiciona o paciente dentro de uma fila de pacientes patient_queue*/
            queue_enqueue_patient(patient_queue, paciente);
            ids += 1;
            
       }
       machine_slots = XRMachineManager(machine_slots, machine_queue, exam_queue, patient_queue, machine_id, exam_id); 
        if (machine_slots != 5 || machine_slots != 0){
            machine_id +=1;
            if (machine_id >5){
                machine_id = 1;
            }
        }
        exam_id = get_last_exam_id(exam_queue);
    }
    /*fecha o arquivo patient_file.txt*/
    fclose(patient_file);

}

