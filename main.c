# include "wildcard.h"

# define TEST 1

volatile	__sig_atomic_t	g_wait = 0;

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);

	# if TEST == 0
	if (ac != 2)
	{
		printf("Usage: %s <regex>\n", av[0]);
		gb_clear();
		return (1);
	}
	char	*regex = av[1];

	printf("regex: %s\n\n", regex);
	print_arr(wildcard(regex, e));
	#endif
	# if TEST == 1
	print_arr(e->envp);	NEWLINE;
	export((char *[]){"a!=1", "b@t=2", "c===3", "d==w=4", "e=t==5", NULL}, e);
	print_arr(e->envp);	NEWLINE;
	unset((char *[]){"a", "b", "c", "d", "e", NULL}, e);
	print_arr(e->envp);
	# endif

	gb_clear();
}
