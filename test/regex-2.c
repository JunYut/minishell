# include "wildcard.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_wildcard	*wc;
	t_env		*e = dup_env(envp);
	char		*regex = "*_module";

	set_val(e, "PWD", "..");
	wc = init_wc(fetch_val("PWD", e));
	wc->token = tokenize(regex);
	print_token(wc->token);
}
