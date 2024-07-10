#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *cmds[] = {"/bin/ls", "/usr/bin/grep", "/usr/bin/wc", NULL};
    char **args[] = {
        (char *[]){"ls", "-l", NULL},
        (char *[]){"grep", "c", NULL},
        (char *[]){"wc", "-l", NULL},
        NULL
    };

    int cmd_count = sizeof(cmds) / sizeof(cmds[0]) - 1;
    int pipe_count = cmd_count - 1;
    int fd[pipe_count][2];

    // Create pipes
    for (int i = 0; i < pipe_count; i++) {
        if (pipe(fd[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < cmd_count; i++) {
        if (fork() == 0) {
            if (i > 0) { // Not the first command
                dup2(fd[i - 1][0], STDIN_FILENO);
            }
            if (i < cmd_count - 1) { // Not the last command
                dup2(fd[i][1], STDOUT_FILENO);
            }
            // Close all fds in child
            for (int j = 0; j < pipe_count; j++) {
                close(fd[j][0]);
                close(fd[j][1]);
            }
            execvp(cmds[i], args[i]);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    // Close all fds in parent
    for (int i = 0; i < pipe_count; i++) {
        close(fd[i][0]);
        close(fd[i][1]);
    }

    // Wait for all child processes
    for (int i = 0; i < cmd_count; i++) {
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
