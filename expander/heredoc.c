/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:38:25 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/11 10:42:55 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "utils.h"

extern char	**environ;

void	heredoc(t_io_node *io, int *p_fd)
{
	char	*doc;

	doc = read_doc(io->exp_value[0]);
	if (!doc)
		exit(0);
	write(p_fd[1], doc, ft_strlen(doc));
	free(doc);
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
		if (!line)
			ft_putstr_fd("minishell: warning: here-document delimited by "
				"end-of-file (wanted `eof')\n", 2);
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		append_str(&doc, line);
		append_str(&doc, "\n");
		init_vars(NULL, NULL)->doc = doc;
		free(line);
	}
	return (doc);
}
