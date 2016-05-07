/*
 ============================================================================
 Name        : ipc_bench.c
 Author      : Sam Durham
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ipc_bench.h"
#include "ipc_pipe.h"
#include "ipc_file.h"
#include "ipc_shm.h"
#include "ipc_sem.h"
#include "ipc_utilities.h"
#include <time.h>
#include <math.h>


int NUM_INTS_TO_COPY = 1048576;
int NUM_TRANSFERS = 10;
//int array_to_copy[1048577];


char* IPC_METHOD_STRINGS[] = {"FILES", "PIPE", "SHARED_MEMORY"};

int element_index;
int stop_index;
long total_send_time;
long iteration_send_time;

int int_size = sizeof(int);

enum PROCESS_TYPE process_type;

struct timespec time_before_send, time_after_send;

send_function_t medium_specific_send;
receive_function_t get_last_element;


char* get_process_name() {
	return (process_type == LEADER) ? "Leader" : "Follower";
}

void set_send_method(enum IPC_METHOD method) {

	switch(method) {

		case FILES:
			medium_specific_send = send_data_via_file;
			break;
		case PIPE:
			medium_specific_send = send_data_via_pipe;
			break;
		case SHARED_MEMORY:
			medium_specific_send = send_data_via_shm;
			break;

	}

}

void set_last_element_getter(enum IPC_METHOD method) {

	switch(method) {

		case FILES:
			get_last_element = get_last_element_via_file;
			break;
		case PIPE:
			get_last_element = get_last_element_via_pipe;
			break;
		case SHARED_MEMORY:
			get_last_element = get_last_element_via_shm;
			break;

	}

}

int get_start_int(int transfer_index) {

	if (process_type == LEADER) {
		return 2 * transfer_index;
	} else {
		return (2 * transfer_index) + 1;
	}

}

int get_stop_int(int transfer_index) {

	if (process_type == LEADER) {
		return pow(2, 20) - 1 + (2 * transfer_index);
	} else {
		return pow(2, 20) + (2 * transfer_index);
	}

}


void send(int start_int, int stop_int) {


	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_before_send);
	medium_specific_send(start_int, stop_int);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time_after_send);

	iteration_send_time = get_time_diff_as_nanoseconds(time_before_send, time_after_send);


}

void sem_up() {
	if (semop(sem_id, &up, 1) == -1) {
		perror("IPC error: semop 'up'");
		exit(1);
	}
}

void sem_down() {
	if (semop(sem_id, &down, 1) == -1) {
		perror("IPC error: semop 'down'");
		exit(1);
	}
}

long follower(enum IPC_METHOD method, int transfer_index) {
	int stop_int = get_stop_int(transfer_index);


	sem_down();
	print_receipt_message(transfer_index, stop_int - 1, get_last_element());
	send(get_start_int(transfer_index), stop_int);
	sem_up();

	return iteration_send_time;

}


long leader(enum IPC_METHOD method, int transfer_index) {
	int stop_int = get_stop_int(transfer_index);

	send(get_start_int(transfer_index), stop_int);
	sem_up();
	sem_down();
	print_receipt_message(transfer_index, stop_int + 1, get_last_element());

	return iteration_send_time;

}

long get_average_send_time(int method_index) {

	total_send_time = 0;

	set_send_method(method_index);
	set_last_element_getter(method_index);
	follower_leader_t process = (process_type == FOLLOWER) ? follower : leader;

	int transfer_index = 0;


	for (transfer_index = 0; transfer_index < NUM_TRANSFERS; ++transfer_index) {
		total_send_time += process(method_index, transfer_index);
	}

	return total_send_time / NUM_TRANSFERS;

}


int main(void) {
	int method_index;
	long average_send_times_of_methods[3];

	sem_id = create_sem();

	initialize_shm();
	intialize_file();
	initialize_pipe();



	pid_t pid = fork();

	process_type = (pid == 0) ? LEADER : FOLLOWER;

	for (method_index = 0; method_index < 3; ++method_index) {
		print_begin_method_message(method_index);
		average_send_times_of_methods[method_index] = get_average_send_time(method_index);
	}

	print_send_times(average_send_times_of_methods);


	wait(NULL);

	return EXIT_SUCCESS;
}
