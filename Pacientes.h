#ifndef _PACIENTES_H
#define _PACIENTES_H
#include <time.h>

typedef struct patient Patient;


Patient* create_patient(int id, const char *name, struct tm* timestamp); 

int get_patient_id(Patient* paciente); 

char* get_patient_name(Patient* paciente); 

struct tm* get_patient_timestamp(Patient *paciente); 

void destroy_patient(Patient *paciente);

#endif