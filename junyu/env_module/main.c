# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	e;

	e.var = dup_env(envp, VAR);
	e.exp = init_export(envp);
	export("", &e);
	// env(&e, VAR);
	// printf("\n");
	// export("", &e);
	// env(&e, VAR);
	// printf("\n");

	gb_clear();
	return 0;
}
