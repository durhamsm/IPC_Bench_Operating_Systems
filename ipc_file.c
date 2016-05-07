

#include "ipc_file.h"

int fd;
char *file_name = "/tmp/buf.txt";

void close_file() {
	close(fd);
}

void open_file_for_write() {
	fd = open(file_name, O_WRONLY);
}

void open_file_for_read() {
	fd = open(file_name, O_RDONLY);
}

int get_last_element_via_file() {
	int buf[1];

	open_file_for_read();

	lseek(fd, -1*int_size, SEEK_END);

	read_ints(fd, buf, int_size);

	close_file();

	return buf[0];

}

void send_data_via_file(int start_int, int stop_int) {
	int element_index;
	open_file_for_write();

	for (element_index = start_int; element_index < stop_int + 1; ++element_index) {
		write(fd, &element_index, int_size);
	}

	close_file();

}

void intialize_file() {

	fd = open(file_name, O_CREAT);
	close(fd);

}


