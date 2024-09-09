/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:29:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/09 14:02:40 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "wildcard.h"

void	expand_node(t_node *node, t_minishell *vars)
{
	if (node->args)
		node->exp_args = expand_args(node->args, vars);
}

char	**expand_args(char *args, t_minishell *vars)
{
	char	**expanded;
	char	**globbed;
	char	*buffer;
	int		i;

	i = -1;
	buffer = gbc_add(expand_params(args, vars));
	expanded = split_args(buffer);
	if (!expanded)
		return (NULL);
	while (expanded[++i])
	{
		if (is_valid_regex(expanded[i]) == true)
		{
			globbed = wildcard(expanded[i], vars->env);
			expanded = insert_string_array(expanded, globbed, i);
			free(globbed);
		}
	}
	i = -1;
	while (expanded[++i])
	{
		expanded[i] = gbc_add(remove_outer_quotes(expanded[i]));
	}
	return (expanded);
}

char	*expand_params(char	*str, t_minishell *vars)
{
	char	*expanded;
	int		i;

	expanded = ft_strdup("");
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			expanded = gnl_strjoin(expanded, handle_squote(str, &i));
		else if (str[i] == '"')
			expanded = gnl_strjoin(expanded, handle_dquote(str, &i, vars));
		else if (str[i] == '$')
			expanded = gnl_strjoin(expanded, handle_dollar(str, &i, vars));
		else
			expanded = gnl_strjoin(expanded, handle_reg_str(str, &i));
	}
	return (expanded);
}

void	init_heredocs(t_node *node, t_minishell *vars)
{
	t_io_node	*io;
	int			p_fd[2];
	pid_t		pid;

	if (node == NULL)
		return ;
	init_heredocs(node->left, vars);
	init_heredocs(node->right, vars);
	io = node->io_list;
	while (io != NULL)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(p_fd);
			io->exp_value = expand_args(io->value, vars);
			pid = fork();
			heredoc_child(io, p_fd, pid);
			wait_status(pid, vars->env);
			io->heredoc = p_fd[0];
			close(p_fd[1]);
		}
		else
			io->exp_value = expand_args(io->value, vars);
		io = io->next;
	}
}

void	heredoc_child(t_io_node *io, int *p_fd, pid_t pid)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		heredoc(io, p_fd);
		exit(0);
	}
}
