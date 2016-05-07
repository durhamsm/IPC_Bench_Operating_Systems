

#ifndef IPC_PIPE_H
#define IPC_PIPE_H

#define _GNU_SOURCE

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "ipc_bench.h"

int pipe_descriptors[2];
int get_last_element_via_pipe();

void send_data_via_pipe(int start_int, int stop_int);




void initialize_pipe();




#endif //IPC_PIPE_H
