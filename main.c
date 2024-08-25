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
    
    /*Define quantas unidade de tempo será usadas*/
    int unit_temp = 43200;
    int report_temp = 0, report_id = 1;
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
    FILE *report_file = fopen("db_report.txt", "a+");
    /*Definição da seed como nula para criar númeroa aleatórios*/
    srand(time(NULL));
    /*Criação de uma fila para as máquinas ocupadas*/
    QueueMachine *machine_queue = queue_create_machine();
    /*Criação da fila de pacientes*/
    QueuePatient *patient_queue = queue_create_patient();
    
    /*Criação da fila de exames e de prioridade*/
    QueueExam *exam_priority_queue = queue_create_exam();
    
    /*Variáveis de Relatório*/
    float caried_exams = 0;
    float percent_report;
    int total_time_report = 0;
    int avarage_report_time;
    int caried_exams_bytime = 0;

    /*Variáveis de Relatório de hora extra*/
    int caried_exams_ET = 0;
    int patients_cared_ET = 0;
    int reports_created_ET=0;
    /*Looping principal, contem a contagem do tempo em "unidades de tempo" e realiza as operações*/
    for (int i = 1; i <= unit_temp; i++) {
        int aux = rand() % 5;
        /*Chegada de um paciente ao hospital*/
        if (aux == 0) {
            time(&segundos);
            data_hora_atual = localtime(&segundos);
            Patient *paciente = create_patient(ids, "nomegenerico", data_hora_atual);
            write_patient_in_file(paciente, patient_file, i);
            queue_enqueue_patient(patient_queue, paciente);
            ids += 1;
            /*Nota dos alunos: não sabemos por que, e nem como, mas esse segmento do código não funciona caso esteja fora da condicional. Em lógica
            era pra ser realizado a todo momento, não só quando aux for igual a zero, mas por algum motivo funciona como deve desta maneira. */
            machine_slots = manage_machine_slots(machine_queue, machine_slots, patient_queue, machine_id);
            machine_id += 1;
            if (machine_id > 5) {
                machine_id = 1;
            }
        }
        /*Contagem dos tempos de exame nas maquinas*/
        run_machine_queue(machine_queue);   
          
        /*Criação do primeiro laudo usando IA + Enfileramento na fila de prioridade dos elementos*/
        if (!queue_is_empty_machine(machine_queue)){
            if (is_timecount_zero(machine_queue)){
                aux_machine = queue_dequeue_machine(machine_queue);
                caried_exams_bytime ++;
                char *aux_codition = create_diagnosis();
                Patient *aux_patient = get_machine_patient(aux_machine);
                int aux_patient_id = get_patient_id(aux_patient);
                struct tm* aux_timestemp = get_patient_timestamp(aux_patient);
                aux_exam = create_exam(exam_id,aux_patient_id,get_machine_id(aux_machine),aux_timestemp,aux_codition, get_diagnostico_prio(aux_codition));
                write_exam_in_file(aux_exam, exam_file);
                enqueue_priority(aux_exam, exam_priority_queue);

                exam_id ++;
                machine_slots++;
                caried_exams++;
                
                free(aux_codition);
                destroy_machine(aux_machine);
            }
        }  
        
        /*Criação do laudo médico seguindo o formato do trabalho*/
        if (!queue_is_empty_exam(exam_priority_queue)){
            time_report_update(exam_priority_queue);
            if (report_temp % 30 == 0){
                Exam *aux_exam_2 = queue_dequeue_exam(exam_priority_queue);
                total_time_report += get_time_report(aux_exam_2);
                Report * aux_report = create_report(aux_exam_2, report_id);
                report_id++;
                write_report_in_file(report_file, aux_report);
                destroy_exam(aux_exam_2);
                destroy_report(aux_report);
            }
            report_temp++;
        }

        if(i%4320 == 0){
            clear_terminal();
            percent_report = (100*(report_id-1))/caried_exams;
            avarage_report_time = (total_time_report/report_id-1);
            printf("Numero de pacientes que visitaram o hospital: %d\n",ids-1);
            printf("Numero de Pacientes em espera: %d\n",get_n_patient_queue(patient_queue));
            printf("Numero de exames ja realizados: %.0f\n", caried_exams);
            printf("Numero de pacientes com laudo %d\n", report_id-1);
            printf("Percentual de exames com laudo: %.3f%%\n", percent_report);
            printf("Tempo medio de espera para laudo: Aprocimadamente %.d unidades de tempo", avarage_report_time);
            printf("\n");
            printf("Numero de exames realizados em ate 7200 unidades de tempo: %d", caried_exams_bytime);
            sleep(1);
            if (i%7200 == 0){
                caried_exams_bytime = 0;
            }
        }

    }
    
    fprintf(report_file,("\n\nLaudos realizados em hora extra\n\n"));
    fprintf(exam_file,("\n\nExames realizados em hora extra\n\n"));
    fprintf(patient_file,("\n\nPacientes atendididos em hora extra\n\n"));

    patients_cared_ET =get_n_patient_queue(patient_queue);
    while (!queue_is_empty_machine(machine_queue) || !queue_is_empty_patient(patient_queue) || !queue_is_empty_exam(exam_priority_queue)) {
        machine_slots = manage_machine_slots(machine_queue, machine_slots, patient_queue, machine_id);
        machine_id += 1;
        if (machine_id > 5) {
            machine_id = 1;
        }
        run_machine_queue(machine_queue);   
        if (!queue_is_empty_machine(machine_queue)){
            if (is_timecount_zero(machine_queue)){
                aux_machine = queue_dequeue_machine(machine_queue);
                char *aux_codition = create_diagnosis();
                Patient *aux_patient = get_machine_patient(aux_machine);
                int aux_patient_id = get_patient_id(aux_patient);
                struct tm* aux_timestemp = get_patient_timestamp(aux_patient);
                aux_exam = create_exam(exam_id, aux_patient_id, get_machine_id(aux_machine), aux_timestemp, aux_codition, get_diagnostico_prio(aux_codition));
                write_exam_in_file(aux_exam, exam_file);
                enqueue_priority(aux_exam, exam_priority_queue);
                caried_exams_ET ++;
                exam_id++;
                machine_slots++;
                caried_exams++;
                free(aux_codition);
                destroy_machine(aux_machine);
            }
        }

        if (!queue_is_empty_exam(exam_priority_queue)){
            if (report_temp % 30 == 0){
                Exam *aux_exam_3 = queue_dequeue_exam(exam_priority_queue);
                Report *aux_report = create_report(aux_exam_3, report_id);
                report_id++;
                reports_created_ET++;
                write_report_in_file(report_file, aux_report);
                destroy_exam(aux_exam_3);
                destroy_report(aux_report);
            }
            report_temp++;
        }
    }
    printf("\n\n");
    printf("Pacientes atendidos em hora extra: %d\n", patients_cared_ET);
    printf("Exames realizados em hora extra: %d\n", caried_exams_ET);
    printf("Laudos realizados em hora extra: %d", reports_created_ET);
    
    queue_free_machine(machine_queue);
    queue_free_exam(exam_priority_queue);
    queue_free_patient(patient_queue);
    /*fecha o arquivo patient_file.txt*/
    fclose(patient_file);
    fclose(exam_file);
    fclose(report_file);
}
