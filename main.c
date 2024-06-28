# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "builtins.h"
# include "commands.h"

int main(void)
{
	t_list	*cmds;
	char *cmd;

	cmd = readline("minishell$ ");
	if (cmd)
	{
		printf("You entered: %s\n", cmd);
		ft_lstadd_back(&cmds, ft_lstnew(init_cmd(cmd)));
		print_cmd(ft_lstlast(cmds)->content);
	}
	free(cmd);
}
