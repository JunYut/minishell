# include "wildcard.h"

# define TEST 0

volatile	__sig_atomic_t	g_wait = 0;

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);

	# if TEST == 1
	char	*regex = "*";
	# endif
	# if TEST == 2
	char	*regex = "*_";
	# endif
	# if TEST == 3
	char	*regex = "w*";
	# endif
	# if TEST == 4
	char	*regex = ".*e";
	# endif
	# if TEST == 5
	char	*regex = "*.*";
	# endif
	# if TEST == 6
	char	*regex = "*.*t";
	# endif
	# if TEST == 7
	char	*regex = ".*o*";
	# endif
	# if TEST == 8
	char	*regex = "*e*e*";
	# endif
	# if TEST == 9
	char	*regex = "fail*";
	# endif
	# if TEST == 10
	char	*regex = "*fail";
	# endif
	# if TEST == 11
	char	*regex = "fail*fail";
	# endif
	# if TEST == 12
	char	*regex = "*fail*fail";
	# endif
	# if TEST == 13
	char	*regex = "fail*fail*";
	# endif
	# if TEST == 14
	char	*regex = "*fail*fail*";
	# endif
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

	gb_clear();
}
