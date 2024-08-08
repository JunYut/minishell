# include "exec.h"

int	cmd_exec(t_cmd_line *cmd, t_env *env)
{
	t_redir	*redirs;
	t_cmd	*cmds;
	int	i;

	redirs = cmd->redirs;
	i = -1;
	while (redirs[++i].type != T_END)
	{
		// redirect
	}
	cmds = cmd->cmds;
	i = -1;
	while (cmds[++i].cmd != NULL)
	{
		// execute command
	}
	return (0);
}
