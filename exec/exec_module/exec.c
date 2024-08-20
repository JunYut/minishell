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
			if (file_io(seq->cmd[i].file, seq->cmd[i].file_count))
				continue;
			if (pipe_io(seq->pipefd, seq->pipe_count, i))
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

int	pipe_io(int *pipefd[2], int pipe_count, int i)
{
	if (i > 0)
		dup2(pipefd[i - 1][0], STDIN_FILENO);
	if (i < pipe_count)
		dup2(pipefd[i][1], STDOUT_FILENO);
	close_pipes(pipefd, pipe_count);
	return (0);
}

int	file_io(t_file *file, int file_count)
{
	int	fd;
	int	old_io[2];
	int	i;

	old_io[0] = dup(STDIN_FILENO);
	old_io[1] = dup(STDOUT_FILENO);
	i = -1;
	while (++i < file_count)
	{
		if (file[i].type == T_REDIN)
			fd = open(file[i].file, O_RDONLY);
		else if (file[i].type == T_REDOUT)
			fd = open(file[i].file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file[i].type == T_APPEND)
			fd = open(file[i].file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			dup2(old_io[0], STDIN_FILENO);
			dup2(old_io[1], STDOUT_FILENO);
			printf("%s: %s\n", file[i].file, strerror(errno));
			return (-1);
		}
		if (file[i].type == T_REDIN)
			dup2(fd, STDIN_FILENO);
		else if (file[i].type == T_REDOUT || file[i].type == T_APPEND)
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	open_pipes(int *pipefd[2], int pipe_count)
{
	int	i;

	i = -1;
	while (++i < pipe_count)
	{
		if (pipe(pipefd[i]) == -1)
		{
			perror("debug");
			return (-1);
		}
	}
	return (0);
}

int	close_pipes(int *pipefd[2], int pipe_count)
{
	int	i;

	i = -1;
	while (++i < pipe_count)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	return (0);
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
