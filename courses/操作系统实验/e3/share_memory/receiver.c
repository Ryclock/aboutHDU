#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 1234
#define SEM_KEY 5678

struct sembuf sem_wait = {0, -1, SEM_UNDO};
struct sembuf sem_signal = {1, 1, SEM_UNDO};

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int shm_id = shmget(SHM_KEY, sizeof(char) * 256, IPC_CREAT | 0666);
    if (shm_id == -1) {
        error("shmget");
    }

    char *shm_p = (char *)shmat(shm_id, NULL, 0);
    if (shm_p == (char *)-1) {
        error("shmat");
    }

    int sem_id = semget(SEM_KEY, 2, IPC_CREAT | 0666);
    if (sem_id == -1) {
        error("semget");
    }

    semop(sem_id, &sem_wait, 1);
    printf("Received message: %s", shm_p);
    strcpy(shm_p, "over");
    semop(sem_id, &sem_signal, 1);

    shmdt(shm_p);

    return 0;
}
