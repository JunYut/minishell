/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:38:25 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/16 14:07:29 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "utils.h"

void	heredoc(t_io_node *io, int *p_fd, t_minishell *vars)
{
	char	*doc;

	doc = read_doc(io->exp_value[0], vars);
	if (!doc)
		exit(0);
	write(p_fd[1], doc, ft_strlen(doc));
	free(doc);
}

char	*read_doc(char *delimiter, t_minishell *vars)
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
		line = expand_heredoc(line, vars);
		append_str(&doc, line);
		append_str(&doc, "\n");
		init_vars(NULL, NULL)->doc = doc;
		free(line);
	}
	return (doc);
}

char	*expand_heredoc(char *line, t_minishell *vars)
{
	char	*expanded;
	int		i;

	expanded = ft_strdup("");
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
			expanded = gnl_strjoin(expanded, handle_dollar(line, &i, vars));
		else
			expanded = gnl_strjoin(expanded, handle_non_var(line, &i));
	}
	free(line);
	return (expanded);
}

char	*handle_non_var(char *line, int *i)
{
	int		start;

	start = *i;
	while (line[*i] && line[*i] != '$')
		(*i)++;
	return (gbc_add(ft_substr(line, start, *i - start)));
}
