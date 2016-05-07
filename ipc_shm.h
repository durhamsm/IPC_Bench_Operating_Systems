
#ifndef IPC_SHM_H
#define IPC_SHM_H

#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

extern int* shm_buf;

int get_last_element_via_shm();

//void send_data_via_shm(int* array_to_copy);
void send_data_via_shm(int start_int, int stop_int);

void initialize_shm();



#endif //IPC_SHM_H
