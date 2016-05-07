

#ifndef IPC_FILE_H
#define IPC_FILE_H

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "ipc_bench.h"




int get_last_element_via_file();

void send_data_via_file(int start_int, int stop_int);
void intialize_file();





#endif //IPC_FILE_H
