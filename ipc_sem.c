

#include "ipc_sem.h"

struct sembuf down = {0, -1, SEM_UNDO}, up = {0, 1, SEM_UNDO};
int	sem_id;
int sem_val;

int create_sem() {

	key_t	sem_key   = ftok("P536S", 'S');  /* key to pass to semget() */

	int	semflg = IPC_CREAT;	      /* semflg to pass to semget() */
	int	nsems  = 1;		      /* nsems to pass to semget() */

	if ((sem_id = semget(sem_key, nsems, semflg)) == -1) {
		perror("semget: semget failed");
		exit(1);
	}

	semctl(sem_id, 0, SETVAL, 0);

	return sem_id;
}

void get_sem_val() {
	semctl(sem_id, 0, GETVAL, &sem_val);
}



