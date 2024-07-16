# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*e;

	e = dup_env(envp);
	simple_export("HELLO=WORLD", e);
	env(e);	printf("\n");
	unset("HOME", e);
	unset("HELLO", e);
	env(e);	printf("\n");
	gb_clear();
	return 0;
}
