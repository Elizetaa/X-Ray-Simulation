#ifndef _EXAMES_H
#define _EXAMES_H


typedef struct{

    int id;
    int patient_id;
    int rx_id;
    struct tm* time;

}Exam;

/*--------------------------------------------
    FUNÇÕES PARA MANIPULAÇÕES DOS EXAMES        
--------------------------------------------*/

Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time); /* Retorna o ID da struct Exam */

void destroy_exam(Exam *exame); /* Libera a memória alocada para struc Exam */

int get_exam_id(Exam *exame); /* Retorna o ID da struct Exam */

int get_exam_patient_id(Exam *exame); /* Retorna o ID do paciente através da struct Exam */

int get_exam_rx_id(Exam *exame); /* Retorna o ID do exame */

struct tm* get_exam_time(Exam *exame); /* Retorna o horário do exame */


#endif