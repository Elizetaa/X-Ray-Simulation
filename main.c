#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "pacientes.h"
#include "exames.h"
#include "Machine.h"
#include <unistd.h>

/*LEIA!! Luiz, fiz mais algumas mudanças no código e agora ele está gerando a fila de prioridades em ordem, pra você rodar o código e ver
por contra própria, abre o CMD e escreve "mingw32-make.exe all", depos escreve "trabalho.exe". Você vai perceber que algumas coisas foram printadas,
a primeira é a fila de prioridade, percebe que quem tem a prioridade mais alta foi printado primeiro por estar na frente da fila, e a segunda
foram as pessoas que entraram nas máquinas mas n tiveram tempo de terminar o exame (Eu queria corrigir isso, se você puder, tenta criar um condicional
que o paciente só vai entrar na máquina se tiver pelo menos 10 unidades de tempo sobrando (a variavel i no looping da main), tamo junto manin.*/

int main()
{       
    /*Declaração de variaveis e structs de tempo*/
    int ids = 1;
    struct tm* data_hora_atual;
    time_t segundos;
    
    
    /*Define as variaveis das máquinas*/
    int machine_slots = 5;
    int machine_id = 1;
    Machine *aux_machine;
    /*Define as variaveis de exame*/
    int exam_id = 1;
    Exam *aux_exam;
    /*Abertura dos arquivos na variável patient_file e exam_file*/
    FILE *patient_file = fopen("db_patient.txt", "a+");
    FILE *exam_file = fopen("db_exam.txt","a+");
    /*Definição da seed como nula para criar númeroa aleatórios*/
    srand(time(NULL));
    /*Criação de uma fila para as máquinas ocupadas*/
    QueueMachine *machine_queue = queue_create_machine();
    /*Criação da fila de pacientes*/
    QueuePatient *patient_queue = queue_create_patient();
    
    /*Criação da fila de exames e de prioridade*/
    QueueExam *exam_queue = queue_create_exam();
    QueueExam *exam_priority_queue = queue_create_exam();
    
    /*Looping principal, contem a contagem do tempo em "unidades de tempo" e realiza as operações*/
    for (int i = 1; i <= 200; i++) {
        int aux = rand() % 5;
        if (aux == 0) {
            time(&segundos);
            data_hora_atual = localtime(&segundos);
            Patient *paciente = create_patient(ids, "nomegenerico", data_hora_atual);
            write_patient_in_file(paciente, patient_file, i);
            queue_enqueue_patient(patient_queue, paciente);
            ids += 1;
            machine_slots = manage_machine_slots(machine_queue, machine_slots, patient_queue, 1, exam_queue, machine_id);
            machine_id += 1;
            if (machine_id > 5) {
                machine_id = 1;
            }
        }

        run_machine_queue(machine_queue);        
        if (!queue_is_empty_machine(machine_queue)){
            if (is_timecount_zero(machine_queue)){
                aux_machine = queue_dequeue_machine(machine_queue);
                char *aux_codition = create_diagnosis();
                Patient *aux_patient = get_machine_patient(aux_machine);
                int aux_patient_id = get_patient_id(aux_patient);
                struct tm* aux_timestemp = get_patient_timestamp(aux_patient);
                aux_exam = create_exam(exam_id,aux_patient_id,get_machine_id(aux_machine),aux_timestemp,aux_codition, get_diagnostico_prio(aux_codition));
                write_exam_in_file(aux_exam, exam_file, i);
                queue_enqueue_exam(exam_queue, aux_exam);
                enqueue_priority(aux_exam, exam_priority_queue);
                exam_id ++;
                machine_slots++;
            }
        }
    }
    queue_print_exam(exam_priority_queue);
    queue_print_machine(machine_queue);
    /*fecha o arquivo patient_file.txt*/
    fclose(patient_file);
    fclose(exam_file);
}
    


