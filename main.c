/*Este programa foi realizado por Luiz Felipe Elizeta e Caio Cesar Coronel, ele simula a realização de laudos de 5 maquinas
de raio-x e cria laudos salvos em um banco de dados. A documentação desse código foi realizada para que qualquer um
possa entender completamente todo o processo do código, caso tenha duvida sobre um funcionamento de uma variável ou
função, basta passar o mouse em cima dela que poderá ver para que ela serve. Agradecimentos especias a alunos e 
pessoas que nos deram apoio para realização deste algoritimo estão no read-me.*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "Pacientes.h"
#include "Exames.h"
#include "Machine.h"
#include <unistd.h>


int main()
{
    /*Declaração de variaveis e structs de tempo*/
    
        /*Tempo Atual*/
        struct tm* data_hora_atual;
        time_t segundos;
    
    /*Define quantas unidade de tempo será usadas*/
        
        /*Numero de iterações do looping principal*/
        int unit_temp = 432;
    
    
    /*Define as variaveis dos pacientes*/
        /*Define se um paciente chegou ao hospital (se for 0) ou não*/
        int aux;
        /*ID do paciente, alterado a cada vez que um paciente é criado*/
        int ids = 1;

    /*Define as variaveis das máquinas*/
        
        /*Numero de maquinas que estarão disponiveis, é alterado a cada vez que um paciente é adicionado ou removido 
        de machine_queue*/
        int machine_slots = 5;
        /*ID das maquinas, revesa a cada vez que um paciente é alocado*/
        int machine_id = 1;
        /*Máquina auxiliar para operações*/
        Machine *aux_machine;
        /*Variavel Auxiliar de máquina*/
        int aux_machine_slot;
    /*Define as variaveis de exame*/
        
        /*ID do exame, alterado a cada vez que um exame é criado*/
        int exam_id = 1;
        /*Exame auxiliar para operações*/
        Exam *aux_exam;
        /*Contador de tempo para calculo de quando o médico deve recolher um exame (definido como 30 iterações)*/
        int report_temp = 0;
        /*ID do laudo*/
        int report_id = 1;

    /*Abertura dos arquivos na variável patient_file e exam_file, report_file*/

        /*Arquivo de paciente*/
        FILE *patient_file = fopen("db_patient.txt", "w");
        /*Arquivo de exame*/
        FILE *exam_file = fopen("db_exam.txt","w");
        /*Arquivo de laudo*/
        FILE *report_file = fopen("db_report.txt", "w");
    
    /*Escreve o cabeçalho nos arquivos*/
    fprintf(patient_file,("ID do Paciente, Nome do Paciente, Hora de entrada do paciente, Data de entrada do paciente, Iteracao do looping\n\n"));
    fprintf(exam_file,("ID do Exame, ID da Maquina Utilizada, ID do Paciente, Condicao do paciente, Prioridade de atendimento, Hora do fim do exame, Data do fim do exame, Iteracao do looping principal\n\n"));
    fprintf(report_file,("ID do Laudo, ID do exame, Nova Condicao do Paciente, Hora de conclusao do laudo, Data de conclusao do laudo, Iteracao do Looping Principal.\n\n"));
    /*Definição da seed como nula para criar númeroa aleatórios*/
    srand(time(NULL));
    
    /*Criação de uma fila para as máquinas ocupadas*/

        /*Fila de maquinas*/
        QueueMachine *machine_queue = queue_create_machine();
    
    /*Criação da fila de pacientes*/
       
        /*Fila de pacientes*/
        QueuePatient *patient_queue = queue_create_patient();
    
    /*Criação da fila de exames e de prioridade*/
        
        /*Fila de exames prioridade*/
        QueueExam *exam_priority_queue = queue_create_exam();
    
    /*Variáveis de Relatório*/
        /*Exames atendidos*/
        float caried_exams = 0;
        /*Porcentagem de laudos realizados*/
        float percent_report;
        /*Tempo total de espera por laudo*/
        int total_time_report = 0;
        /*Tempo medio de espera por laudo*/
        int avarage_report_time;
        /*Exames realizados por tempo definido*/
        int caried_exams_bytime = 0;
        /*Tempo total de espera de pacientes com condição assinalada*/
        int marked_codition_total_time = 0;
        /*Tempo medio de condição assinalada pelo medico*/
        int marked_codition_avarage_time = 0;
        /*Condição assinalada pelo medico*/
        char *condicao_assinalada = "Tuberculose";
        /*Exame auxiliar para operações*/
        Exam *aux_exam_2 = NULL;

    /*Variáveis de Relatório apos o looping principal*/
        /*Exames realizados ao fim do looping principal*/
        int caried_exams_ET = 0;
        /*Pacientes atendidos apos o tempo principal*/
        int patients_cared_ET = 0;
        /*Laudos realizados apos o tempo do looping principal*/
        int reports_created_ET=0;
        /*Numero de pacientes com condição assinalada*/
        int n_condicao_assinalada = 0;   
    /*Looping principal, contem a contagem do tempo em "unidades de tempo" e realiza as operações*/
    for (int i = 1; i <= unit_temp; i++) {
        /*Chance de 1 em cinco do paciente chegar ao hospital*/
        aux = rand() % 5;
        /*Chegada de um paciente ao hospital*/
        if (aux == 0) {
            /*Paciente é criado*/
            time(&segundos);
            data_hora_atual = localtime(&segundos);
            Patient *paciente = create_patient(ids, "nomegenerico", data_hora_atual);
            /*Paciente é salvo em db_patient*/
            write_patient_in_file(paciente, patient_file, i);
            /*Paciente é colocado em uma fila de pacientes*/
            queue_enqueue_patient(patient_queue, paciente);
            ids += 1;
        }

        /**/
        aux_machine_slot = machine_slots;
        machine_slots = manage_machine_slots(machine_queue, machine_slots, patient_queue, machine_id); 
        if(aux_machine_slot != machine_slots)
            machine_id = machine_id%5 + 1;

        /*Contagem dos tempos de exame nas maquinas*/
        run_machine_queue(machine_queue);   
          
        /*Criação do primeiro laudo usando IA + Enfileramento na fila de prioridade dos elementos*/
        if (!queue_is_empty_machine(machine_queue) && is_timecount_zero(machine_queue)){
            /*Checa se o paciente deve sair da máquina*/
                
            /*Paciente sai da máquina*/
            aux_machine = queue_dequeue_machine(machine_queue);
            if (i <=7200){
                caried_exams_bytime ++;
            }    
            /*Cria um diagnostico*/
            char *aux_codition = create_diagnosis();
                
            /*Recolhe as informações para criação do exame*/
            Patient *aux_patient = get_machine_patient(aux_machine);
            int aux_patient_id = get_patient_id(aux_patient);
            struct tm* aux_timestemp = get_patient_timestamp(aux_patient);
                
            /*Exame é criado*/
            aux_exam = create_exam(exam_id,aux_patient_id,get_machine_id(aux_machine),aux_timestemp,aux_codition, get_diagnostico_prio(aux_codition));
                
            /*Escreve as informações no banco de dados de exame*/
            write_exam_in_file(aux_exam, exam_file, i);
                
            /*Aloca o paciente em uma fila de exames de prioridade*/
            enqueue_priority(aux_exam, exam_priority_queue);

            exam_id ++;
            machine_slots++;
            caried_exams++;
                
        }  
        
        /*Cria laudos médicos*/

        /*Verifica se a fila de exames não está vazia*/
        if (!queue_is_empty_exam(exam_priority_queue) || aux_exam_2 != NULL){
            /*Atualiza o tempo em que os pacientes estão aguardando, para somar a média*/
            time_report_update(exam_priority_queue);
            if (report_temp == 30){
                /*Cria o laudo médico e escreve ele no banco de dados*/
                Report * aux_report = create_report(aux_exam_2, report_id);
                report_id++;
                write_report_in_file(report_file, aux_report, i);
                report_temp = 0;
            }
            if (report_temp == 0){
                aux_exam_2 = queue_dequeue_exam(exam_priority_queue);
                /*Adiciona o tempo de espera à média*/
                total_time_report += get_time_report(aux_exam_2)-1;
                if (strcmp(condicao_assinalada, get_exam_condition(aux_exam_2)) == 0){
                    n_condicao_assinalada +=1;
                    marked_codition_total_time += get_time_report(aux_exam_2)-1;
                }
            }
            report_temp++;
        }
        /*Impressão eventual de relatórios, será realizada 100 vezes*/
        if(i%432 == 0){
            
            /*Calcula os dados de média de tempo e porcentagem de exames com laudo*/
            percent_report = (100*(report_id-1))/caried_exams;
            avarage_report_time = (total_time_report/report_id-1);
            clear_terminal();
            marked_codition_avarage_time = (marked_codition_total_time/n_condicao_assinalada);
            /*Impressão das informações*/
            printf("%d\n", n_condicao_assinalada);
            printf("%d\n", marked_codition_total_time);
            printf("\nNumero de pacientes que visitaram o hospital: %d\n",ids-1);
            printf("Numero de Pacientes em espera: %d\n",get_n_patient_queue(patient_queue));
            printf("Numero de exames ja realizados: %.0f\n", caried_exams);
            printf("Numero de pacientes com laudo %d\n", report_id-1);
            printf("Percentual de exames com laudo: %.3f%%\n", percent_report);
            printf("Tempo medio de espera por atendimento de pacientes com %s: %d\n", condicao_assinalada, marked_codition_avarage_time);
            printf("Tempo medio de espera para laudo: Aproximadamente %.d unidades de tempo\n", avarage_report_time);
            printf("Numero de exames realizados em ate 7200 unidades de tempo: %d\n", caried_exams_bytime);
            usleep(5000);
            
        }

    }

    /*Impressão de cabeçalho*/
    fprintf(report_file,("\n\nLaudos realizados em hora extra\n\n"));
    fprintf(exam_file,("\n\nExames realizados em hora extra\n\n"));
    fprintf(patient_file,("\n\nPacientes atendididos em hora extra\n\n"));
    
    /*Coleta relatório numero de pacientes na fila para relatório*/
    patients_cared_ET = get_n_patient_queue(patient_queue);

    /*Realização dos exames restantes fora do horário padrão, até que todas as filas estejam vazias*/
    /*Looping que para quando a fila de maquinas, a fila de pacientes e a fila de exames estiverem vazias*/
    while (!queue_is_empty_machine(machine_queue) || !queue_is_empty_patient(patient_queue) || !queue_is_empty_exam(exam_priority_queue)) {
        /*Variavel auxiliar para comparação*/
        int aux_machine_slot = machine_slots;
        machine_slots = manage_machine_slots(machine_queue, machine_slots, patient_queue, machine_id);
        /*Compara a variavel auxiliar com o numero de vagas disponiveis, se alterado, a maquina se alterna*/
        if(aux_machine_slot != machine_slots)
            machine_id = machine_id%5 + 1;

        /*Diminui a contagem dos tempos de exame nas maquinas*/
        run_machine_queue(machine_queue);

        /*Caso a fila de maquinas não esteja vazia, e o médico esteja disponivel*/   
        if (!queue_is_empty_machine(machine_queue) &&is_timecount_zero(machine_queue)){
            
            /*Cria um diagnostico, e associa o paciente da maquina removida a um exame*/
            aux_machine = queue_dequeue_machine(machine_queue);
            char *aux_codition = create_diagnosis();
            Patient *aux_patient = get_machine_patient(aux_machine);
            int aux_patient_id = get_patient_id(aux_patient);
            struct tm* aux_timestemp = get_patient_timestamp(aux_patient);
            aux_exam = create_exam(exam_id, aux_patient_id, get_machine_id(aux_machine), aux_timestemp, aux_codition, get_diagnostico_prio(aux_codition));
            
            /*Escreve o exame em db_exam*/
            write_exam_in_file(aux_exam, exam_file, 0);
            
            /*Exame entra em uma fila de prioridade*/
            enqueue_priority(aux_exam, exam_priority_queue);
            
            caried_exams_ET ++;
            exam_id++;
            machine_slots++;
            caried_exams++;
            
        }
        /*Caso a fila de prioridades não esteja vazia, e o médico terminou o exame, ele realiza o laudo*/
        if (!queue_is_empty_exam(exam_priority_queue)){
            if (report_temp % 30 == 0){
                Exam *aux_exam_3 = queue_dequeue_exam(exam_priority_queue);
                Report *aux_report = create_report(aux_exam_3, report_id);
                report_id++;
                reports_created_ET++;
                write_report_in_file(report_file, aux_report, 0);
            }
            report_temp++;
        }
    }
    /*Impressão de relatório de hora extra*/
    printf("\nFim das 43200 unidades de tempo\n");
    printf("\n\n");
    printf("Pacientes atendidos apos as unidades de tempo: %d\n", patients_cared_ET);
    printf("Exames realizados apos as unidades de tempo: %d\n", caried_exams_ET);
    printf("Laudos realizados apos as unidades de tempo: %d\n", reports_created_ET);

    /* Liberação da memória restante */
    queue_free_machine(machine_queue);

    /* Libera a fila de pacientes */
    queue_free_patient(patient_queue);

    /* Libera a fila de exames */
    queue_free_exam(exam_priority_queue);

    /* Libera os ponteiros auxiliares usados que ainda não foram liberados */
    
    if (aux_machine) {
        destroy_machine(aux_machine);
    }
    
    /* Fechamento dos arquivos */
    fclose(patient_file);
    fclose(exam_file);
    fclose(report_file);
    printf("Fim do programa.\n");
}
