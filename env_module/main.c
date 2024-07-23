# include "env.h"
# include "gbc.h"
# include <string.h>
# include <stdio.h>

# define TEST 0

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*e;

	e = dup_env(envp);

	# if TEST == 1
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("/home/we/Programming/42kl", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("../C", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("..", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd(".", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("/home/we/Programming/42kl/42_Cursus/", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("-", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("~we", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("-", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("~", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("-", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("-", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd(NULL, e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");

	cd("../not exist", e);
	printf("cwd: %s\n", gb_add(getcwd(NULL, 0)));
	printf("PWD: %s\n", fetch_val("PWD", e));
	printf("OLDPWD: %s\n", fetch_val("OLDPWD", e));
	printf("\n");
	# endif

	# if TEST == 2
	pwd(e);
	cd("../", e);
	pwd(e);
	#endif

	char *strs[] = {"Hello", "World", NULL};
	echo(strs);

	gb_clear();
	return 0;
}