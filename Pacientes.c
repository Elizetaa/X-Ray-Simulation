#include "pacientes.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



struct patient{

    int id;
    char *name;
    struct tm* timestamp;

};

Patient* create_patient(int id, const char *name, struct tm* timestamp){

    Patient* pont = (Patient*)malloc(sizeof(Patient*));
    assert(pont != NULL && timestamp != NULL && name != NULL);

    strcpy(pont->name,name);
    memcpy(pont->timestamp, timestamp, sizeof(struct tm));
    pont->id = id;
    

    return pont;
}

int get_patient_id(Patient* paciente){ 
    return paciente->id;
}

char* get_patient_name(Patient* paciente){ 
    return paciente->name;
}

struct tm* get_patient_timestamp(Patient *paciente){ 
    return paciente->timestamp;
}

void destroy_patient(Patient *paciente){ 
    free(paciente->name);
    free(paciente);
}

