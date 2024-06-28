# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "builtins.h"
# include "commands.h"

int main(void)
{
	char *cmd_line;

	cmd_line = readline("minishell$ ");
	if (cmd_line)
	{
		printf("You entered: %s\n", cmd_line);
	}
	free(cmd_line);
}
