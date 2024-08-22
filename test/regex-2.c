# include "wildcard.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);
	char	*regex = "*_module";

	set_val(e, "PWD", "..");
	print_arr(wildcard(regex, e));	NEWLINE;
}
