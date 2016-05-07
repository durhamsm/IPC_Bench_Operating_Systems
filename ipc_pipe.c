

#include "ipc_pipe.h"
#define _GNU_SOURCE

int pipe_descriptors[2];

int get_last_element_via_pipe() {

	int buf[NUM_INTS_TO_COPY];

	read_ints(pipe_descriptors[0], buf, NUM_INTS_TO_COPY * int_size);
	return buf[NUM_INTS_TO_COPY - 1];
}

void send_data_via_pipe(int start_int, int stop_int) {
	int element_index = 0;

	for (element_index = start_int; element_index < stop_int + 1; ++element_index) {
		write(pipe_descriptors[1], &element_index, int_size);
	}

}

void initialize_pipe() {
	pipe(pipe_descriptors);
	fcntl(pipe_descriptors[1], F_SETPIPE_SZ, NUM_INTS_TO_COPY * int_size);
}
