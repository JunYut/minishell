# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_var	*e;

	e = dup_env(envp);
	add_var("HELLO=WORLD", e);
	env(e);	printf("\n");
	unset("PATH", e);
	unset("HELLO", e);
	env(e);	printf("\n");
	gb_clear();
	return 0;
}
