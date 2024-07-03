# include <readline/readline.h>
# include <stdio.h>
# include "commands.h"
# include "parser.h"
# include "builtins.h"
# include "utils.h"
# include "debug.h"

# define DEBUG 1

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_list	*cmds;
	char *cmd;

	// Executing one command line
	cmd = readline("minishell$ ");
	if (cmd)
	{
		cmds = ft_lstnew(init_cmd(cmd, envp));
		print_cmd(cmds->content);
	}
	free(cmd);
	printf("access: %d\n", access("commands/", X_OK));

	// TODO: Executing multiple command lines
}
