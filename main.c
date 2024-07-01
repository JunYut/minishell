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


	printf("is_cmd: %d\n", is_cmd("/usr/bin/echo"));	// debug
	printf("path: %s\n", parse_path(envp, "echo"));	// debug
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
