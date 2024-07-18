# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	e;

	e.var = init_var(envp);
	e.exp = init_export(envp);

	export("", &e);
	printf("\n");
	env(&e, VAR);

	gb_clear();
	return 0;
}
