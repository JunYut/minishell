# include "wildcard.h"

# define TEST 1

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);

	# if TEST == 1
	char	*regex = "*";
	# endif
	# if TEST == 2
	char	*regex = ".*";
	# endif
	# if TEST == 3
	char	*regex = ".*gi";
	# endif
	# if TEST == 4
	char	*regex = "*_module";
	# endif
	# if TEST == 5
	char	*regex = "e*";
	# endif
	# if TEST == 6
	char	*regex = "e*e";
	# endif
	# if TEST == 7
	char	*regex = "*e*e*";
	# endif

	print_arr(wildcard(regex, e));	NL;

	gb_clear();
}
