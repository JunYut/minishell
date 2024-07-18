# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	e;

	e.exp = init_export(envp);
	export(NULL, &e);
	printf("\n");
	export("a", &e);
	export(NULL, &e);
	printf("\n");

	gb_clear();
	return 0;
}
