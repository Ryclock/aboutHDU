#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>

#define NUM_CHILDREN 3

int main() {
    int pipe_fd[2];
    pid_t child_pids[NUM_CHILDREN];
    sem_t *mutex;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    mutex = sem_open("/my_semaphore", O_CREAT | O_EXCL, 0666, 1);
    if (mutex == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    fcntl(pipe_fd[1], F_SETFL, fcntl(pipe_fd[1], F_GETFL) | O_NONBLOCK);

    for (int i = 0; i < NUM_CHILDREN; ++i) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            close(pipe_fd[0]);

            for (int j = 0; j < 10000; ++j) {
                char message[50];
                sprintf(message, "Message from Child %d, iteration %d\n", i, j + 1);

                sem_wait(mutex);
                ssize_t bytes_written = write(pipe_fd[1], message, strlen(message));
                sem_post(mutex);

                if (bytes_written == -1) {
                    if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        fprintf(stderr, "Child %d write failed (pipe full)\n", i);
                    } else {
                        perror("write");
                    }
                    break;
                }
            }

            close(pipe_fd[1]);
            exit(EXIT_SUCCESS);
        }
        child_pids[i] = child_pid;
    }

    for (int i = 0; i < NUM_CHILDREN; ++i) {
        waitpid(child_pids[i], NULL, 0);
    }

    close(pipe_fd[1]);

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    fprintf(stderr, "Read completed (pipe empty)\n");

    close(pipe_fd[0]);

    sem_close(mutex);
    sem_unlink("/my_semaphore");

    return 0;
}
