# include "wildcard.h"
# include "env.h"

# define TEST 1

volatile	__sig_atomic_t	g_wait = 0;

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);
	int		status;

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
	printf("pwd: %s\n", fetch_val("PWD", e));
	cd((char *[]){"noperm", NULL}, e);
	printf("pwd: %s\n", fetch_val("PWD", e));
	# endif

	status = ft_atoi(fetch_val("?", e));
	gb_clear();
	return (status);
}
