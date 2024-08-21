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
		free(line);
	}
}

void	do_stuff()
{
	int		i;

	i = 0;
	while (i < 1000000)
	{
		i++;
	}
}

void	int_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
