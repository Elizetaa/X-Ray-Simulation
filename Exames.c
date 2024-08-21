#include "exames.h"
#include <time.h>
#include <stdlib.h>

/*--------------------------------------------
    FUNÇÕES PARA MANIPULAÇÕES DOS EXAMES        
--------------------------------------------*/

Exam* create_exam(int id, int patient_id, int rx_id, struct tm *time){ /* Retorna o ID da struct Exam */
    Exam* exame = (Exam*)malloc(sizeof(Exam*));
    if (exame == NULL)
        return NULL;
    exame->id = id;
    exame->patient_id = patient_id;
    exame->rx_id = rx_id;
    exame->time = time;

    return exame;
}

void destroy_exam(Exam *exame){ /* Libera a memória alocada para struc Exam */
    free(exame->time);
    free(exame);
}

int get_exam_id(Exam *exame){ /* Retorna o ID da struct Exam */
    return exame->id;
}

int get_exam_patient_id(Exam *exame){ /* Retorna o ID do paciente através da struct Exam */
    return exame->patient_id;
}

int get_exam_rx_id(Exam *exame){ /* Retorna o ID do exame */
    return exame->rx_id;
}

struct tm* get_exam_time(Exam *exame){ /* Retorna o horário do exame */
    return exame->time;
}