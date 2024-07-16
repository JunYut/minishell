# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*e;
	t_gbc	gbc;

	gb_init(&gbc);
	e = dup_env(envp, &gbc);
	export("HELLO=WORLD", e, &gbc);
	env(e);	printf("\n");
	unset("HOME", e);
	unset("HELLO", e);
	env(e);	printf("\n");
	gb_clear(&gbc);
	return 0;
}
