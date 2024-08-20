# include "exec.h"
# include "debug.h"

int	exec(t_cmd_line *cmd, t_env *e)
{
	int	i;

	i = -1;
	while (++i < cmd->seq_count)
	{
		if (cmd->seq[i].type == T_AND && ft_atoi(fetch_val("?", e)) != 0)
			continue ;
		if (cmd->seq[i].type == T_OR && ft_atoi(fetch_val("?", e)) == 0)
			continue ;
		cmd->pid[i] = fork();
		if (cmd->pid[i] == 0)
		{
			open_pipes(cmd->seq[i].pipefd, cmd->seq[i].pipe_count);
			pipex(&cmd->seq[i], e->envp);
			close_pipes(cmd->seq[i].pipefd, cmd->seq[i].pipe_count);
			wait_childs(cmd->seq[i].pid, cmd->seq_count, e);
			exit(EXIT_SUCCESS);
		}
		wait_status(cmd->pid[i], e);
	}
	return (0);
}

int	pipex(t_pipe *seq, char *envp[])
{
	int	i;

	i = -1;
	while (++i < seq->cmd_count)
	{
		seq->pid[i] = fork();
		if (seq->pid[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (seq->pid[i] == 0)
		{
			if (pipe_io(seq->pipefd, seq->pipe_count, i))
				continue;
			if (file_io(seq->cmd[i].file, seq->cmd[i].file_count))
				continue;
			if (exec_cmd(seq->cmd[i].cmd, seq->cmd[i].argv, envp))
				continue;
		}
	}
	return (0);
}

int	exec_cmd(char *path, char *argv[], char *envp[])
{
	execve(path, argv, envp);
	perror(path);
	exit(EXIT_FAILURE);
}

int	wait_childs(pid_t *pid, int count, t_env *e)
{
	int	status;
	int	i;

	i = -1;
	while (++i < count)
		status = wait_status(pid[i], e);
	return (status);
}

// returns -1 on abnormal termination
// returns the exit status of the child process (0-255)
int	wait_status(pid_t pid, t_env *e)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (0);
	else if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		set_val(e, "?", (char *)gb_add(ft_itoa(status)));
	}
	else
	{
		status = -1;
		printf("PID %d: terminated abnormally\n", pid);
	}
	return (status);
}
