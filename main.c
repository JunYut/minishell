# include <readline/readline.h>
# include <readline/history.h>
# include "builtins.h"

int main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		add_history(line);
		free(line);
	}
	rl_clear_history();
}
