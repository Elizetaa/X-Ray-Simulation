#include "pacientes.h"
#include <time.h>
#include <stdlib.h>

/*--------------------------------------------
    FUNÇÕES PARA MANIPULAÇÕES DOS PACIENTES        
--------------------------------------------*/

Patient* create_patient(int id, const char *name, struct tm *birthdate){

    Patient* pont = (Patient*)malloc(sizeof(Patient*));
    if (pont == NULL)
        return NULL;
    pont->id = id;
    pont->name = name;
    pont->birthdate = birthdate;

    return pont;
}

int get_patient_id(Patient* paciente){ /* Retorna o ID da struct Patient */
    return paciente->id;
}

char* get_patient_name(Patient* paciente){ /* Retorna o nome da struct Patient */
    return paciente->name;
}

struct tm* get_patient_birthdate(Patient *paciente){ /* Retorna a data de nascimento da struct Patient */
    return paciente->birthdate;
}

void destroy_patient(Patient *paciente){ /* Deleta o registro da memória */
    free(paciente->name);
    free(paciente->birthdate);
    free(paciente);
}

