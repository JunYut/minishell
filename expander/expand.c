/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:29:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/06 15:24:49 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "wildcard.h"

bool	is_valid_regex(char *str);
char	**insert_string_array(char **dest, char **src, int insert_index);
int		count_strings(char **array);

void	expand_node(t_node *node, t_minishell *vars)
{
	if (node->args)
		node->exp_args = expand_args(node->args, vars);
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
			if (!pid)
			{
				signal(SIGINT, SIG_DFL);
				heredoc(io, p_fd);
			}
			wait_status(pid, vars->env);
			io->heredoc = p_fd[0];
			close(p_fd[1]);
		}
		else
			io->exp_value = expand_args(io->value, vars);
		io = io->next;
	}
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
		expanded[i] = gbc_add(remove_quotes(expanded[i]));
	}
	return (expanded);
}

bool	is_valid_regex(char *str)
{
	if (!str || *str == '\'' || *str == '"' || !*str)
		return (false);
	return (is_in_set('*', str));
}

int	count_strings(char **array)
{
	int	count;

	count = 0;
	if (!array || !array[0])
		return (0);
	while (array[count] != NULL)
		count++;
	return (count);
}

char	**insert_string_array(char **dest, char **src, int insert_index)
{
	int		dest_size;
	int		src_size;

	dest_size == count_strings(dest);
	src_size = count_strings(src);
	if (insert_index < 0 || insert_index > dest_size)
	{
		printf("Invalid insertion index.\n");
		return (NULL);
	}
	char	**new_dest = malloc((dest_size + src_size + 1) * sizeof(char *));
	if (new_dest == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < insert_index; i++)
	{
		new_dest[i] = (dest)[i];
	}
	for (int i = 0; i < src_size; i++)
	{
		new_dest[insert_index + i] = src[i];
	}
	for (int i = insert_index; i < dest_size; i++)
	{
		new_dest[src_size + i] = (dest)[i + 1];
	}
	new_dest[dest_size + src_size] = NULL;
	free(dest);
	return (new_dest);
}

char	*expand_params(char	*str, t_minishell *vars)
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
			expanded_str = gnl_strjoin(expanded_str, handle_dquote(str, &i, vars));
		else if (str[i] == '$')
			expanded_str = gnl_strjoin(expanded_str, handle_dollar(str, &i, vars));
		else
			expanded_str = gnl_strjoin(expanded_str, handle_reg_str(str, &i));
	}
	return (expanded_str);
}

char	*handle_reg_str(char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i] != '\0' && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (gbc_add(ft_substr(str, start, *i - start)));
}

char	*handle_squote(char *str, int *i)
{
	int		start;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquote_str(char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquote(char *str, int *i, t_minishell *vars)
{
	char	*ret_str;

	ret_str = ft_strdup("\"");
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			ret_str = gnl_strjoin(ret_str, handle_dollar(str, i, vars));
		else
			ret_str = gnl_strjoin(ret_str, handle_dquote_str(str, i));
	}
	(*i)++;
	return (gnl_strjoin(ret_str, "\""));
}

char	*handle_dollar(char *str, int *i, t_minishell *vars)
{
	int		start;
	char	*val;
	char	*env_val;

	(*i)++;
	if (str[*i] == '\0' || str[*i] == '"' || str[*i] == ' ')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	if (str[*i] == '?')
	{
		(*i)++;
		return (fetch_val("?", vars->env));
	}
	if (is_valid_var_char(str[*i] == false))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	start = *i;
	while (is_valid_var_char(str[*i]) == true)
		(*i)++;
	val = ft_substr(str, start, *i - start);
	env_val = fetch_val(val, vars->env);
	if (env_val == NULL)
		return (free(val), ft_strdup(""));
	return (free(val), env_val);
}

bool	is_valid_var_char(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (true);
	return (false);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;
	char	quote;

	if (!str || !*str)
		return (ft_strdup(""));
	i = -1;
	j = 0;
	quote = 0;
	while (str[++i])
	{
		if (quote == 0 && (str[i] == '"' || str[i] == '\''))
			quote = str[i];
		if (str[i] == quote)
			j++;
	}
	new_str = ft_calloc(ft_strlen(str) - j + 1, sizeof(char));
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] != quote)
			new_str[j++] = str[i];
	}
	free(str);
	return (new_str);
}
