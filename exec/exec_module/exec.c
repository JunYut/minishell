# include "exec.h"
# include "debug.h"

int	exec(t_cmd_line *cmd, t_env *env)
{
	int	i;
	int	j;

	i = -1;
	while (++i < cmd->seq_count)
	{
		if (cmd->seq->type == T_AND && ft_atoi(fetch_val(env, "?")) != 0)
			continue ;
		if (cmd->seq->type == T_OR && fta_atoi(fetch_val(env, "?")) == 0)
			continue ;
		cmd->pid[i] = fork();
		if (cmd->pid[i] == 0)
		{
			j = -1;
			open_pipes(cmd->seq[i].pipefd, cmd->seq[i].pipe_count);
			while (++j < cmd->seq->cmd_count)
				pipex();
			close_pipes(cmd->seq[i].pipefd, cmd->seq[i].pipe_count);
			wait_childs(cmd->pid, cmd->seq_count, env);
		}
		wait_status(cmd->pid[i], env);
	}
	return (0);
}

int	exec_cmd(char *path, char *argv[], char *envp[])
{
	execve(path, argv, envp);
	perror(path);
	exit(EXIT_FAILURE);
}

int	pipe_io(t_token type, int pipefd[][2], int pipe_count)
{
	int	i;

	i = -1;
	while (++i < pipe_count)
	{
		if (type != T_PIPE_START)
			dup2(pipefd[i][0], STDIN_FILENO);
		if (type != T_PIPE_END)
			dup2(pipefd[i][1], STDOUT_FILENO);
	}
	return (0);
}

int	file_io(t_file *file, int file_count)
{
	int	fd;
	int	i;

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
			return (-1);
		if (file[i].type == T_REDIN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

int	open_pipes(int pipefd[][2], int pipe_count)
{
	int	i;

	i = -1;
	while (++i < pipe_count)
		if (pipe(pipefd[i]) == -1)
			return (-1);
	return (0);
}

int	close_pipes(int pipefd[][2], int pipe_count)
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

int	wait_childs(pid_t *pid, int count, t_env *env)
{
	int	status;
	int	i;

	i = -1;
	while (++i < count)
		status = wait_status(pid[i], env);
	return (status);
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
