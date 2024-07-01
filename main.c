# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "builtins.h"
# include "commands.h"
# include "utils.h"

# define DEBUG 1

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_list	*cmds;
	char *cmd;


	printf("is_cmd: %d\n", is_cmd("/usr/bin/echo"));	// debug
	// Executing one command line
	cmd = readline("minishell$ ");
	if (cmd)
	{
		printf("You entered: %s\n", cmd);
		cmds = ft_lstnew(init_cmd(cmd, envp));
		print_cmd(cmds->content);
	}
	free(cmd);

	// TODO: Executing multiple command lines
}
