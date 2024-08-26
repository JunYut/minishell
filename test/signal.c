# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

void	shell();
void	do_stuff();
void	int_sigint(int sig);
void	int_sigquit(int sig);

int	g_wait = 0;

int main(void)
{
	shell();
	return (0);
}

void	shell()
{
	char	*line;

	signal(SIGINT, int_sigint);
	signal(SIGQUIT, int_sigquit);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line || strcmp(line, "exit") == 0)
		{
			if (!line)
				printf("\n");
			printf("exit\n");
			if (line)
				free(line);
			break ;
		}
		add_history(line);
		if (strcmp(line, "do") == 0)
			do_stuff();
		free(line);
	}
}

void	do_stuff()
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		printf("do_stuff\n");
		execve("/usr/bin/sleep", (char *[]){"sleep", "5", NULL}, NULL);
		perror("sleep");
		exit(EXIT_FAILURE);
	}
	g_wait = 1;
	waitpid(pid, NULL, 0);
	g_wait = 0;
}

void	int_sigint(int sig)
{
	(void)sig;
	printf("\n");
	if (!g_wait)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	int_sigquit(int sig)
{
	(void)sig;
	if (g_wait)
		printf("Quit\n");
}
