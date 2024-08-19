#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "pacientes.h"
#include "exames.h"
#include "queue.h"



int main()
{  
    QueuePatient *queue_patient = queue_create();
    time_t tempoAtual;
    time(tempoAtual);
    
    struct tm *timestamp = localtime(&tempoAtual);

    

    printf("xablau");

    return 0;
}