# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	e;

	init_env(&e, envp);

	env(&e, EXPORT);

	cd(NULL, &e);

	gb_clear();
	return 0;
}
