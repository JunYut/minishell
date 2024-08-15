# include "wildcard.h"

# define TEST 1

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*env = dup_env(envp);

	# if TEST == 1
	char	*regex = "*";
	# endif

	print_arr(wildcard(regex, env));

	gb_clear();
}
