# include "wildcard.h"

# define TEST 1

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);

	char	*regex1 = "*";


	print_arr(wildcard(regex1, e));	NEWLINE;
	print_lst(init_wc(fetch_val("PWD", e))->files);	NEWLINE;
	print_lst(init_wc(fetch_val("PWD", e))->dot_files);	NEWLINE;
	cd("..", e);
	print_arr(wildcard(regex1, e));	NEWLINE;
	print_lst(init_wc(fetch_val("PWD", e))->files);	NEWLINE;
	print_lst(init_wc(fetch_val("PWD", e))->dot_files);	NEWLINE;

	gb_clear();
}
