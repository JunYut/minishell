/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:29:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/05 18:21:10 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void	expand_tree(t_node *node)
{
	char **envp = environ;

	if (node == NULL)
		return ;
	if (node->type ==  N_PIPE || node->type == N_AND || node->type == N_OR)
	{
		expand_tree(node->left);
		expand_tree(node->right);
	}
	expand_node(node);
	if (node->io_list != NULL && node->io_list->type == IO_OUT)
		append(node->io_list->value, parse_path(envp, node->exp_args[0]), node->exp_args);
	else
	{
		pid_t pid = fork();
		if (pid == 0)
			execve(parse_path(envp, node->exp_args[0]), node->exp_args, NULL);
		wait(NULL);
	}
}

void	expand_node(t_node *node)
{
	t_io_node	*io;

	if (node->args)
		node->exp_args = expand_args(node->args);
	io = node->io_list;
	while (io != NULL)
	{
		// printf("redir_type: %d\n", io->type);
		// printf("redir: %s\n", io->value);
		io = io->next;
	}
}

char	**expand_args(char *args)
{
	char	**expanded;
	char	*buffer;
	int		i;

	(void)i;

	buffer = expand_params(args);
	printf("expanded: %s\n", buffer);
	expanded = ft_split(buffer, ' ');
	return (expanded);
}

char	*expand_params(char	*str)
{
	char	*expanded_str;
	int		i;

	expanded_str = ft_strdup("");
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			expanded_str = gnl_strjoin(expanded_str, handle_squote(str, &i));
		else if (str[i] == '"')
			expanded_str = gnl_strjoin(expanded_str, handle_dquote(str, &i));
		else if (str[i] == '$')
			expanded_str = gnl_strjoin(expanded_str, handle_dollar(str, &i));
		else
			expanded_str = gnl_strjoin(expanded_str, handle_reg_str(str, &i));
	}
	return (expanded_str);
}

char	*handle_reg_str(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '\0' && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_squote(char *str, int *i)
{
	int		start;

	start = *i + 1;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start - 1));
}

char	*handle_dquote_str(char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquote(char *str, int *i)
{
	char	*ret_str;

	// ret_str = ft_strdup("\"");
	ret_str = ft_strdup("");
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			ret_str = gnl_strjoin(ret_str, handle_dollar(str, i));
		else
			ret_str = gnl_strjoin(ret_str, handle_dquote_str(str, i));
	}
	(*i)++;
	// return (gnl_strjoin(ret_str, "\""));
	return (ret_str);
}

char	*handle_dollar(char *str, int *i)
{
	int		start;
	char	*val;
	char	*env_val;

	(*i)++;
	if (is_valid_var_char(str[*i] == false))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	start = *i;
	while (is_valid_var_char(str[*i]) == true)
		(*i)++;
	val = ft_substr(str, start, *i - start);
	env_val = fetch_val(val, dup_env(environ));
	if (env_val == NULL)
		return (free(val), ft_strdup(""));
	return (free(val), env_val);
}

bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}
