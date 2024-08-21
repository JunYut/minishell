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
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (strcmp(line, "exit") == 0)
		{
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
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		printf("do_stuff\n");
		execve("/usr/bin/sleep", (char *[]){"sleep", "10", NULL}, NULL);
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
