

#ifndef IPC_UTILITIES_H
#define IPC_UTILITIES_H


#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void print_receipt_message(int transfer_index, int expected_last_element, int actual_last_element);

long get_time_diff_as_nanoseconds(struct timespec time1, struct timespec time2);

void print_send_times(long times_in_nanos[]);

void print_begin_method_message(int method_index);

void read_ints(int descriptor, int* read_buf, int bytes_to_read);

#endif //IPC_UTILITIES_H
