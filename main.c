# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "builtins.h"
# include "commands.h"

# define DEBUG 1

int main(void)
{
	t_list	*cmds;
	char *cmd;

	// Executing one command line
	cmd = readline("minishell$ ");
	if (cmd)
	{
		printf("You entered: %s\n", cmd);
		cmds = ft_lstnew(init_cmd(cmd));
		print_cmd(cmds->content);
	}
	free(cmd);

	// TODO: Executing multiple command lines
}
