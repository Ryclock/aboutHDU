#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 1234
#define SEM_KEY 5678

struct sembuf sem_wait = {1, -1, SEM_UNDO};
struct sembuf sem_signal = {0, 1, SEM_UNDO};

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
    semctl(sem_id, 0, SETVAL, 0);
    semctl(sem_id, 1, SETVAL, 0);

    printf("Enter a string: ");
    fgets(shm_p, 256, stdin);
    semop(sem_id, &sem_signal, 1);

    semop(sem_id, &sem_wait, 1);
    printf("Receiver response: %s\n", shm_p);

    shmdt(shm_p);
    shmctl(shm_id, IPC_RMID, NULL);

    semctl(sem_id, 0, IPC_RMID);

    return 0;
}
