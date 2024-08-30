# include "env.h"

int	pwd(t_env *e)
{
	printf("%s\n", fetch_val("PWD", e));
	return (0);
}
