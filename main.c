# include <readline/readline.h>
# include <readline/history.h>
# include "builtins.h"
# include "commands.h"

int main(void)
{
	t_cmd_table	commands;
	char		*line;

	while (1)
	{
		line = readline("\033[0;33mminishell\033[0m$ ");
		add_history(line);
		printf("[%s]\n", line);	// Debug
		if (ft_strcmp(line, "exit") == 0)
			break;
		// ft_lstadd_back(&commands.cmd, ft_lstnew());
		free(line);
	}
	free(line);
	ft_lstclear(&commands.cmd, free_cmd);
	rl_clear_history();
}
