#ifndef _EXAMES_H
#define _EXAMES_H
#include <time.h>

typedef struct Exame Exam;


Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time, const char *condition_IA); 

void destroy_exam(Exam *exame); 

int get_exam_id(Exam *exame); 

int get_exam_patient_id(Exam *exame); 

int get_exam_rx_id(Exam *exame); 

struct tm* get_exam_time(Exam *exame); 


#endif