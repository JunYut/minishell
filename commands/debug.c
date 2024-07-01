# include "commands.h"

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->identifiers[++i])
		printf("identifiers[%d]: %s\n", i, cmd->identifiers[i]);
	printf("i: %d\n", i);
	i = -1;
	while (cmd->tokens[++i] != T_INVALID)
		printf("tokens[%d]: %d\n", i, cmd->tokens[i]);
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
