# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

int main(void)
{
    char *cmds[] =
    {
        "/bin/ls",
        "/usr/bin/wc",
    };
    char *args[][3] =
    {
        {"ls", NULL, NULL},
        {"wc", "-l", NULL},
    };
    pid_t	pid[2];
    int		pipefd[2];
    int exit_status;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork the first child process
    pid[0] = fork();
    if (pid[0] == 0) {
        // Child process 1: Execute 'ls'
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
        close(pipefd[1]); // Close write end after duplicating
        execve(cmds[0], args[0], NULL);
        perror("ls"); // Print error if execve fails
        _exit(1); // Exit child process if execve fails
    }

    // Fork the second child process
    pid[1] = fork();
    if (pid[1] == 0) {
        // Child process 2: Execute 'wc -l'
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe read end
        close(pipefd[0]); // Close read end after duplicating
        execve(cmds[1], args[1], NULL);
        perror("wc"); // Print error if execve fails
        _exit(1); // Exit child process if execve fails
    }

    // Parent process: Close both ends of the pipe
    close(pipefd[0]);
    close(pipefd[1]);

    // Wait for both child processes to finish
    for (int i = 0; i < 2; i++) {
        waitpid(pid[i], &exit_status, 0);
        if (WIFEXITED(exit_status))
            printf("Success exit[%d][%d]: %d\n", i, pid[i], WEXITSTATUS(exit_status));
        else
            printf("Fail exit[%d][%d]: %d\n", i, pid[i], exit_status);
    }

    return 0;
}
