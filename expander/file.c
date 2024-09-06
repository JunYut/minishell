/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:18:06 by we                #+#    #+#             */
/*   Updated: 2024/09/06 15:53:03 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	append(char *file, char *cmd, char *args[])
{
	char	*content;
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		execve(cmd, args, NULL);
	}
	close(pipefd[1]);
	wait(NULL);
	content = read_pipe(pipefd[0]);
	write_file(file, content);
	free(content);
	close(pipefd[0]);
}

void	write_file(char *file, char *content)
{
	int	fd;

	fd = open(file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	write(fd, content, ft_strlen(content));
	close(fd);
}

char	*read_pipe(int read_fd)
{
	char	*content;
	char	*tmp;
	int		bytes_read;

	content = malloc(1);
	tmp = malloc(READ_SIZE + 1);
	content[0] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(read_fd, tmp, READ_SIZE);
		tmp[bytes_read] = '\0';
		content = gnl_strjoin(content, tmp);
	}
	free(tmp);
	return (content);
}
