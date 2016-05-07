

#ifndef IPC_BENCH_H
#define IPC_BENCH_H

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/sem.h>

#include <sys/stat.h>
#include <fcntl.h>


extern struct sembuf down, up;

extern char *lock_name;

extern int sem_id;
extern int sem_val;



enum IPC_METHOD {FILES, PIPE, SHARED_MEMORY};
extern char* IPC_METHOD_STRINGS[];

enum PROCESS_TYPE {LEADER, FOLLOWER};
extern enum PROCESS_TYPE process_type;


long leader(enum IPC_METHOD method, int transfer_index);
long follower(enum IPC_METHOD method, int transfer_index);
char* get_process_name();
long get_total_send_time();


extern int NUM_INTS_TO_COPY;
//extern int array_to_copy[];
extern int element_index;
extern int int_size;

typedef  void (*send_function_t)(int, int);
typedef  int (*receive_function_t)();
typedef  long (*follower_leader_t)(enum IPC_METHOD, int);

#endif //IPC_BENCH_H
