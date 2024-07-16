# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_env	*e;
	t_gbc	gbc;

	gb_init(&gbc);
	// e = dup_env(envp, &gbc);
	e = gb_malloc(&gbc, sizeof(t_env));
	e->next = NULL;
	e = dup_env(envp, &gbc);
	env(e);
	export("HELLO=WORLD", e, &gbc);
	env(e);
	gb_free(&gbc);
	return 0;
}
