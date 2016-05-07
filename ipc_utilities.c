

#include "ipc_utilities.h"
#include "ipc_bench.h"


void print_receipt_message(int transfer_index, int expected_last_element, int actual_last_element) {
	//print statements used during debugging
//	printf("%s %d\n", get_process_name(), transfer_index);
//	printf("Expected Last element:\t %d\nActual Last Element:\t %d\n", expected_last_element, actual_last_element);
	printf("\nExpected Last element:\t %d\nActual Last Element:\t %d\n", expected_last_element, actual_last_element);


	if (expected_last_element != actual_last_element) {
		printf("Error!!\nExpected Last element:\t %d\nActual Last Element:\t %d\n", expected_last_element, actual_last_element);
	}
}

long get_time_diff_as_nanoseconds(struct timespec time1, struct timespec time2) {
	return 1000000000 * (time2.tv_sec - time1.tv_sec) + time2.tv_nsec - time1.tv_nsec;
}

void print_send_times(long times_in_nanos[]) {
	int method_index;

	if (process_type == FOLLOWER) {
		sleep(5);
	}

	printf("\n%s, Average time (microsecs) per send:\n\n", get_process_name());

	for (method_index = 0; method_index < 3; ++method_index) {
		printf("%-15s->%10ld\n", IPC_METHOD_STRINGS[method_index], times_in_nanos[method_index] / 1000);
	}

}

void print_begin_method_message(int method_index) {
	printf("%s began %s transfers\n", get_process_name(), IPC_METHOD_STRINGS[method_index]);
}

void read_ints(int descriptor, int* read_buf, int bytes_to_read) {

	if (read(descriptor, read_buf, bytes_to_read) < 1) {
		printf("Error!! Read failed");
		exit(1);
	}

}





