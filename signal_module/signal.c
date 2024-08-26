# include "signals.h"

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
