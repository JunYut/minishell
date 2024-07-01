# include "enum.h"
# include "commands.h"
# include "debug.h"

void	print_cmd(t_cmd_line *cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd->identifiers[++i])
		printf("identifiers[%d]: %s\n", i, cmd->identifiers[i]);
	printf("\n");
	i = -1;
	while (cmd->tokens[++i] != T_INVALID)
		printf("tokens[%d]: %d\n", i, cmd->tokens[i]);
	printf("\n");
	i = -1;
	while (cmd->cmds[++i].cmd)
	{
		printf("cmd[%d]: %s\n", i, cmd->cmds[i].cmd);
		j = -1;
		while (cmd->cmds[i].args[++j])
			printf("args[%d]: %s\n", j, cmd->cmds[i].args[j]);
	}
}

void	print_paths(char **path_list)
{
	while (*path_list)
	{
		printf("%s\n", *path_list);
		++path_list;
	}
}

void	debug(char *msg)
{
	static int	i;

	if (!DEBUG)
		return ;
	if (msg)
		printf("\033[0;33mDEBUG[%d]: %s\033[0m\n", i, msg);
	else
		printf("\033[0;33mDEBUG[%d]\033[0m\n", i);
	++i;
}
