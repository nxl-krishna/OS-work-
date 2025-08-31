#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();   // Step 1: Fork a new process

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process
        printf("Child (PID: %d) running new.c executable...\n", getpid());

        // Step 2: Run ./new using execvp
        char *args[] = {"./new", NULL};   // executable name, NULL terminated
        if (execvp(args[0], args) == -1) {
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
    }
    else {
        // Parent process
        printf("Parent (PID: %d) waiting for child...\n", getpid());

        // Step 3: Wait for child
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child did not terminate normally\n");
        }
    }

    return 0;
}
