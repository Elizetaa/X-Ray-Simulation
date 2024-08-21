#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pacientes.h"
#include "exames.h"
#include "queue.h"

int main()
{  

    struct tm birthdate = {0}; 
    birthdate.tm_year = 90; 
    birthdate.tm_mon = 5; 
    birthdate.tm_mday = 15; 
    
    Patient *patient = create_patient(1, "João Silva", &birthdate);

    printf("Paciente criado:\n");
    printf("ID: %d\n", get_patient_id(patient));
    printf("Nome: %s\n", get_patient_name(patient));
    printf("Data de Nascimento: %s\n", asctime(get_patient_birthdate(patient)));

    time_t current_time;
    struct tm *exam_time;

    current_time = time(NULL); 
    exam_time = localtime(&current_time); 

    Exam *exam = create_exam(101, get_patient_id(patient), 1, exam_time);

    printf("\nExame criado:\n");
    printf("ID: %d\n", get_exam_id(exam));
    printf("ID do Paciente: %d\n", get_exam_patient_id(exam));
    printf("ID do Aparelho de Raio-X: %d\n", get_exam_rx_id(exam));
    printf("Data e Hora do Exame: %s\n", asctime(get_exam_time(exam)));


    Queue *fila = q_create();

    q_enqueue(fila, patient);

    return 0;
}