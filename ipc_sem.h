

#ifndef IPC_SEM_H
#define IPC_SEM_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>


extern int sem_id;
extern int sem_val;

int create_sem();
void get_sem_val();


#endif //IPC_SEM_H
