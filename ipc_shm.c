
#include "ipc_shm.h"
#include "ipc_bench.h"

int* shm_buf;

int get_last_element_via_shm() {
	return shm_buf[NUM_INTS_TO_COPY - 1];
}

//void send_data_via_shm(int* array_to_copy) {
void send_data_via_shm(int start_int, int stop_int) {
	int buf_index = 0;

	for (element_index = start_int; element_index < stop_int + 1; ++element_index) {
		shm_buf[buf_index++] = element_index;
	}

}



void initialize_shm() {

	key_t	shm_key   = ftok("P536B", 'B');
	int   size   = NUM_INTS_TO_COPY;
	int   shm_id;
	struct shmid_ds ds;

	if (-1 == (shm_id = shmget(shm_key, size*sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR ))) {
		perror("shmem");
		exit(1);
	}

	if (-1 == shmctl(shm_id, IPC_STAT, &ds)) {
		perror("shmctl");
		exit(1);
	}

	/* Attach shared memory segment */
	shm_buf = (int *) shmat(shm_id, 0, 0);


}
