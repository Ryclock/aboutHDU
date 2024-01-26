#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100

void execute_command(char *command)
{
    char path[255];
    snprintf(path, sizeof(path), "/tmp/bin/%s", command);
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        execlp(path, command, NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        printf("Child process exited with status %d\n", WEXITSTATUS(status));
    }
    else
    {
        printf("Child process did not exit normally\n");
    }
}

int main()
{
    char command[MAX_COMMAND_LENGTH];

    while (1)
    {
        printf("Enter a command (type 'exit' to quit): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting myshell\n");
            break;
        }

        execute_command(command);
    }

    return 0;
}
