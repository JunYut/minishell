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
	// char	buf[1024];

	e = dup_env(envp);

	env(e, VAR);
	printf("\n");

	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("~", e);
	printf("\n");

	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("~", e);
	printf("\n");

	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	gb_clear();
	return 0;
}
