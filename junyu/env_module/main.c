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

	init_env(&e, envp);

	// export("LMAO=lol", &e);
	// export("LMAO=kek", &e);
	// env(&e, VAR);

	cd("..", &e);

	gb_clear();
	return 0;
}
