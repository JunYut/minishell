# include "env.h"

void	pwd(t_env *e)
{
	printf("%s\n", fetch_val("PWD", e));
}
