# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env	*e;
	t_gbc	gbc;

	gb_init(&gbc);
	e = dup_env(env, &gbc);
	gb_free(&gbc);
	return 0;
}
