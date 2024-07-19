# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_env	e;
	// char	buf[1024];

	init_env(&e, envp);

	// env(&e, VAR);
	printf("PWD: %s\n", fetch_val("PWD", e.var));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e.var));
	printf("\n");

	// printf("getcwd(): %s\n", getcwd(buf, sizeof(buf)));
	cd("-", &e);
	// printf("getcwd(): %s\n", getcwd(buf, sizeof(buf)));

	printf("PWD: %s\n", fetch_val("PWD", e.var));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e.var));
	printf("\n");

	gb_clear();
	return 0;
}
