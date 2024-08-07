# include "pipe.h"
# include "redir.h"
# include "env.h"
# include "signal.h"
# include "libft.h"
# include "gbc.h"
# include "define.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_env	*e = dup_env(envp);

	env(e, EXPORT);

	gb_clear();
}
