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
		if (i && cmds[i].logical == T_AND && wait_status(pid, env) != 0)
			continue ;
		else if (i && cmds[i].logical == T_OR && wait_status(pid, env) == 0)
			continue ;
		pid = fork();
		if (pid == 0)
		{
			execve(cmds[i].cmd, cmds[i].argv, env->envp);
			printf("%s: command not found\n", cmds[i].argv[0]);
			exit(EXIT_FAILURE);
		}
		close_fds(env, cmds[i].type, pid, );
	}
	i = -1;
	while (cmds[++i].type != T_END)
		if (cmds[i].type == T_CMD)
			wait_status(pid, env);
	return (0);
}

int	redirect(t_redir *redirs)
{
	int	i;

	i = -1;
	while (redirs[++i].type != T_END)
	{
		if (redirs[i].type == T_AND || redirs[i].type == T_OR)
			continue ;
		if (redirs[i].type == T_REDIN)
			redin(redirs[i].file);
		else if (redirs[i].type == T_REDOUT || redirs[i].type == T_APPEND)
			redout_o(redirs[i].file, redirs[i].type);
		// else if (redirs[i].type == T_PIPE)
		// 	pipex(redirs[i].file);
		else if (redirs[i].type == T_HERE_DOC)
			heredoc(redirs[i].file);
	}
	return (0);
}

int	close_fds(t_env *env, t_token type, pid_t pid, int *fds)
{
	if (type == T_REDOUT || type == T_APPEND || type == T_PIPE)
		wait_status(pid, env);
	else
		return (0);
	if (type == T_REDOUT || type == T_APPEND)
		redout_c(fds[3], fds[0], (int[2]){fds[1], fds[2]});
	else
		;
	return (0);
}

// returns -1 on abnormal termination
// returns the exit status of the child process (0-255)
int	wait_status(pid_t pid, t_env *env)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (0);
	else if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		set_val(env, "?", (char *)gb_add(ft_itoa(status)));
	}
	else
	{
		status = -1;
		printf("PID %d: terminated abnormally\n", pid);
	}
	return (status);
}
