#ifndef _EXAMES_H
#define _EXAMES_H
#include <time.h>

typedef struct Exame Exam;
typedef struct queue_exam QueueExam;
typedef struct queue_node_exam QueueNodeExam; 


QueueExam *queue_create_exam();

int queue_is_empty_exam(QueueExam *queue);

void queue_enqueue_exam(QueueExam *queue, Exam *data);

Exam *queue_dequeue_exam(QueueExam *queue);

void queue_print_exam(QueueExam *queue);

Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time, const char *condition_IA, int prio); 

void destroy_exam(Exam *exame); 

int get_exam_id(Exam *exame); 

int get_exam_patient_id(Exam *exame); 

int get_exam_rx_id(Exam *exame); 

struct tm* get_exam_time(Exam *exame); 

int get_last_exam_id(QueueExam *exam_queue);

#endif