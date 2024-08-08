# include "exec.h"
# include "utils.h"

int	cmd_exec(t_cmd_line *cmd, t_env *env)
{
	redirect(cmd->redirs);
	execute(cmd->cmds, env);
	return (0);
}

int	redirect(t_redir *redirs)
{
	int	i;

	i = -1;
	while (redirs[++i].type != T_END)
	{
		// redirect
	}
	return (0);
}

int	execute(t_cmd *cmds, t_env *env)
{
	pid_t	pid;
	int		exit_status;
	int		i;

	i = -1;
	while (cmds[++i].cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			DPRINTF("executing %s ", cmds[i].cmd);
			print_arr(cmds[i].argv);
			execve(cmds[i].cmd, cmds[i].argv, NULL);
			exit(0);
		}
	}
	i = -1;
	while (cmds[++i].cmd != NULL)
	{
		exit_status = wait(NULL);
		DPRINTF("exit status: %d\n", exit_status);
		set_val(env, "?", ft_itoa(exit_status));
	}
	return (0);
}
