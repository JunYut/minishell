# include <readline/readline.h>
# include <readline/history.h>
# include "builtins.h"
# include "commands.h"

int main(void)
{
	t_list	*commands;
	char	*line;

	while (1)
	{
		line = readline("\033[0;33mminishell\033[0m$ ");
		add_history(line);
		if (ft_strcmp(line, "exit") == 0)
			break;
		ft_lstadd_back(NULL, ft_lstnew(ft_split(line, ' ')));
		free(line);
	}
	free(line);
	rl_clear_history();
}
