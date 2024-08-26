# include "env.h"

void	pwd(char **argv, t_env *e)
{
	(void)argv;

	printf("%s\n", fetch_val("PWD", e));
}
