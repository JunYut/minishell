#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#define PROGRAM 0
#define PIPE_COUNT 4

# if PROGRAM == 1
int main() {
	# if PIPE_COUNT == 1
	char *cmds[] =
	{
		"/bin/cat",
		"/usr/bin/grep",
		NULL
	};
	char **args[] =
	{
		(char *[]){"cat", "main.c", NULL},
		(char *[]){"grep", "#", NULL},
		NULL
	};
	# endif
	# if PIPE_COUNT == 2
	char *cmds[] =
	{
		"/bin/ls",
		"/usr/bin/grep",
		"/usr/bin/wc",
		NULL
	};
	char **args[] =
	{
		(char *[]){"ls", "-l", NULL},
		(char *[]){"grep", "c", NULL},
		(char *[]){"wc", "-l", NULL},
		NULL
	};
	# endif
	# if PIPE_COUNT == 3
	char *cmds[] =
	{
		"/bin/ls",
		"/usr/bin/grep",
		"/usr/bin/sort",
		"/bin/cat",
		NULL
	};
	char **args[] =
	{
		(char *[]){"ls", NULL},
		(char *[]){"grep", "c", NULL},
		(char *[]){"sort", "-r", NULL},
		(char *[]){"cat", "-e", NULL},
		NULL
	};
	# endif
	# if PIPE_COUNT == 4
	char *cmds[] =
	{
		"/bin/echo",
		"/usr/bin/tr",
		"/usr/bin/tr",
		"/usr/bin/sort",
		"/usr/bin/uniq",
	};
	char **args[] =
	{
		(char *[]){"echo", "Hello, World!", NULL},
		(char *[]){"tr", "\' \'", "\'-\'", NULL},
		(char *[]){"tr", "\'e\'", "\'E\'", NULL},
		(char *[]){"sort", NULL},
		(char *[]){"uniq", NULL},
	};
	# endif
	# if PIPE_COUNT == 5
	char *cmds[] =
	{
		"/bin/echo",
		"/usr/bin/tr",
		"/usr/bin/sort",
		"/usr/bin/uniq",
		"/usr/bin/tr",
		"/usr/bin/awk",
		NULL
	};
	char **args[] =
	{
		(char *[]){"echo", "Sample text for pipe demonstration", NULL},
		(char *[]){"tr", "\' \'", "\'\\n\'", NULL},
		(char *[]){"sort", NULL},
		(char *[]){"uniq", NULL},
		(char *[]){"tr", "\'a-z\'", "\'A-Z\'", NULL},
		(char *[]){"awk", "{print $0 \"-PIPE\"}", NULL},
	};
	# endif
	# if PIPE_COUNT == 6
	char *cmds[] =
	{
		"/bin/cat",
		"/usr/bin/tr",
		"/usr/bin/tr",
		"/usr/bin/sort",
		"/usr/bin/uniq",
		"/usr/bin/sort",
		"/usr/bin/head",
		NULL
	};
	char **args[] =
	{
		(char *[]){"cat", "main.c", NULL},
		(char *[]){"tr", "\'[:upper:]\'", "\'[:lower:]\'", NULL},
		(char *[]){"tr", "-c", "\'[:alnum:]\'", "\'\\n\'", NULL},
		(char *[]){"sort", NULL},
		(char *[]){"uniq", "-c", NULL},
		(char *[]){"sort", "-nr", NULL},
		(char *[]){"head", "-10", NULL},
		NULL
	};
	# endif

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
# endif
