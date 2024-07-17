# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_var	*e;

	e = init_export(envp);
	env(e);

	gb_clear();
	return 0;
}
