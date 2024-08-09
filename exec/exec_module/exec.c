# include "exec.h"
# include "debug.h"

int	cmd_exec(t_cmd_line *cmd, t_env *env)
{
	redirect(cmd->redirs);
	execute(cmd->cmds, env);
	return (0);
}

int	execute(t_cmd *cmds, t_env *env)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (cmds[++i].type != T_END)
	{
		if (i && cmds[i].type == T_AND)
		{
			DPRINTF("AND[%d]: ", i);
			exit_status(pid, env);
			if (ft_atoi(fetch_val("?", env)) != 0)
				continue ;
		}
		if (i && cmds[i].type == T_OR)
		{
			DPRINTF("OR[%d]: ", i);
			exit_status(pid, env);
			if (ft_atoi(fetch_val("?", env)) == 0)
				continue ;
		}
		pid = fork();
		if (pid == 0)
		{
			execve(cmds[i].cmd, cmds[i].argv, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		DPRINTF("> [%d]executing: ", pid);
		DPRINT_ARR(cmds[i].argv);
	}
	i = -1;
	while (cmds[++i].type != T_END)
	{
		if (cmds[i].type == T_AND || cmds[i].type == T_OR)
			continue;
		exit_status(pid, env);
	}
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

int	exit_status(pid_t pid, t_env *env)
{
	int	exit_status;

	waitpid(pid, &exit_status, 0);
	exit_status = WEXITSTATUS(exit_status);
	set_val(env, "?", (char *)gb_add(ft_itoa(exit_status)));
	DPRINTF("PID %d: %s\n", pid, fetch_val("?", env));
	return (exit_status);
}
