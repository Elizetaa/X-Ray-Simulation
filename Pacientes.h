#ifndef _PACIENTES_H
#define _PACIENTES_H


typedef struct{

    int id;
    char *name;
    struct tm *birthdate;

} Patient;

/*--------------------------------------------
    FUNÇÕES PARA MANIPULAÇÕES DOS PACIENTES        
--------------------------------------------*/

Patient* create_patient(int id, const char *name, struct tm *birthdate); /* Retorna um ponteiro para uma estrutura alocada na memória */

int get_patient_id(Patient* paciente); /* Retorna o ID da struct Patient */

char* get_patient_name(Patient* paciente); /* Retorna o nome da struct Patient */

struct tm* get_patient_birthdate(Patient *paciente); /* Retorna a data de nascimento da struct Patient */

void destroy_patient(Patient *paciente); /* Deleta o registro da memória */

#endif