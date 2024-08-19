#include "exames.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



struct Exame{

    int id;
    int rx_id;
    int patient_id;
    char *condition_IA;
    struct tm* timestamp;

};



Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time, const char *condition_IA){ 
    Exam* exame = (Exam*)malloc(sizeof(Exam));
    assert(exame != NULL && time != NULL && condition_IA != NULL);

    memcpy(exame->timestamp, time, sizeof(struct tm));

    strcpy(exame->condition_IA, condition_IA);

    if (exame == NULL || exame->timestamp == NULL || exame->condition_IA == NULL)
        return NULL;

    exame->id = id;
    exame->patient_id = patient_id;
    exame->rx_id = rx_id;
    return exame;
}

void destroy_exam(Exam *exame){
    free(exame->condition_IA);
    free(exame);
}

int get_exam_id(Exam *exame){
    return exame->id;
}

int get_exam_patient_id(Exam *exame){
    return exame->patient_id;
}

int get_exam_rx_id(Exam *exame){
    return exame->rx_id;
}

struct tm* get_exam_time(Exam *exame){
    return exame->timestamp;
}