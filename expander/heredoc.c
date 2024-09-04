/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:38:25 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/04 14:54:42 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

extern char **environ;

// void	heredoc(char *delimiter, char *cmd, char *args[])
// {
// 	char	*doc;
// 	pid_t	pid;
// 	int		fd[2];

// 	doc = read_doc(delimiter);
// 	if (cmd)
// 	{
// 		pipe(fd);
// 		write(fd[1], doc, ft_strlen(doc));
// 		close(fd[1]);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			dup2(fd[0], STDIN_FILENO);
// 			execve(cmd, args, NULL);
// 		}
// 		close(fd[0]);
// 		wait(NULL);
// 	}
// 	free(doc);
// }

void	heredoc(t_io_node *io, int *p_fd)
{
	char	*doc;

	doc = read_doc(io->exp_value[0]);
	// pipe(p_fd);
	write(p_fd[1], doc, ft_strlen(doc));
	// close(p_fd[1]);
	// dup2(p_fd[0], STDIN_FILENO);
	// close(p_fd[0]);
	free(doc);
	exit(0);
}

char	*read_doc(char *delimiter)
{
	char	*doc;
	char	*line;

	doc = malloc(1);
	doc[0] = '\0';
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		append_str(&doc, line);
		append_str(&doc, "\n");
		free(line);
	}
	return (doc);
}

// void	append_str(char **str1, char *str2)
// {
// 	int		i;
// 	int		j;
// 	char	*new;

// 	i = -1;
// 	j = -1;
// 	new = malloc(ft_strlen(*str1) + ft_strlen(str2) + 1);
// 	while ((*str1)[++i])
// 		new[i] = (*str1)[i];
// 	while (str2[++j])
// 		new[i + j] = str2[j];
// 	new[i + j] = '\0';
// 	free(*str1);
// 	*str1 = new;
// }
