/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:29:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/01 15:54:07 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "wildcard.h"

bool	is_valid_regex(char *str);
char **insert_string_array(char **dest, char **src, int insert_index);
int count_strings(char **array);

char	*get_node_type(int type)
{
	if (type == N_PIPE)
		return ("PIPE");
	else if (type == N_AND)
		return ("AND");
	else if (type == N_OR)
		return ("OR");
	else
		return ("CMD");
}

void	print_tree(t_node *node, int depth, char *branch)
{
	if (depth != 0)
		printf("├─");
	for (int i = 1; i < depth; ++i) {
		printf("─");  // Indentation based on depth
	}
	printf("Node(%s): %s | Value: %s\n", branch, get_node_type(node->type), node->args);
}

void	init_heredocs(t_node *node, t_minishell *vars)
{
	t_io_node	*io;
	int	p_fd[2];
	pid_t	pid;

	if (node == NULL)
		return ;
	if (node->type ==  N_PIPE || node->type == N_AND || node->type == N_OR)
	{
		init_heredocs(node->left, vars);
		init_heredocs(node->right, vars);
	}
	io = node->io_list;
	while (io != NULL)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(p_fd);
			io->exp_value = expand_args(io->value, vars);
			pid = fork();
			if (!pid)
				heredoc(io, p_fd);
			waitpid(pid, &pid, 0);
			io->heredoc = p_fd[0];
		}
		else
			io->exp_value = expand_args(io->value, vars);
		io = io->next;
	}
}

void	expand_node(t_node *node, t_minishell *vars)
{
	// t_io_node	*io;
	// int			p_fd[2];
	// pid_t		pid;

	if (node->args)
		node->exp_args = expand_args(node->args, vars);
	// io = node->io_list;
	// while (io != NULL)
	// {
	// 	// if (io->type == IO_HEREDOC)
	// 	// {
	// 	// 	pipe(p_fd);
	// 	// 	io->exp_value = expand_args(io->value, vars);
	// 	// 	pid = fork();
	// 	// 	if (!pid)
	// 	// 		heredoc(io, p_fd);
	// 	// 	waitpid(pid, &pid, 0);
	// 	// 	io->heredoc = p_fd[0];
	// 	// }
	// 	// // printf("redir_type: %d\n", io->type);
	// 	// // printf("redir: %s\n", io->value);
	// 	// else
	// 		io->exp_value = expand_args(io->value, vars);
	// 	// printf("redir_type: %d\n", io->type);
	// 	io = io->next;
	// }
	// printf("exp_args: %s\n", node->args);
}

char	**expand_args(char *args, t_minishell *vars)
{
	char	**expanded;
	char	**globbed;
	char	*buffer;
	int		i;
	(void)vars;
	(void)globbed;

	i = -1;
	buffer = gb_add(expand_params(args, vars));
	expanded = split_args(buffer);
	while (expanded[++i])
	// while (++i <= 2)
	{
		if (is_valid_regex(expanded[i]) == true)
		{
			globbed = wildcard(expanded[i], vars->env);
			expanded = insert_string_array(expanded, globbed, i);
			// print_arr(expanded); DPRINTF("\n");
			free(globbed);
		}
	}
	i = -1;
	while (expanded[++i])
	{
		expanded[i] = gb_add(remove_quotes(expanded[i]));
		// printf("Final string: %s\n", expanded[i]);
	}
	// if (globbed)
	// 	print_arr(globbed);
	return (expanded);
}

bool	is_valid_regex(char *str)
{
	if (!str || *str == '\'' || *str == '"')
		return (false);
	return (is_in_set('*', str));
}

int count_strings(char **array)
{
	int count = 0;

	if (!array || !array[0])
		return (0);
	while (array[count] != NULL) {
		count++;
	}
	return count;
}

char **insert_string_array(char **dest, char **src, int insert_index) {
	// Count the size of dest and src arrays
	int dest_size = count_strings(dest);
	int src_size = count_strings(src);

	// Check if the insertion index is valid
	if (insert_index < 0 || insert_index > dest_size) {
		printf("Invalid insertion index.\n");
		return (NULL);
	}

	// Allocate memory for the new array size (dest_size + src_size + 1 for the NULL terminator)
	char **new_dest = malloc((dest_size + src_size + 1) * sizeof(char *));
	if (new_dest == NULL) {
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}

	// Copy elements before the insertion index
	for (int i = 0; i < insert_index; i++) {
		new_dest[i] = (dest)[i];
	}

	// Insert the new elements from the source array
	for (int i = 0; i < src_size; i++) {
		new_dest[insert_index + i] = src[i];
	}

	// Copy the remaining elements after the insertion index
	for (int i = insert_index; i < dest_size; i++) {
		new_dest[src_size + i] = (dest)[i + 1];
	}

	// Add the NULL terminator at the end
	new_dest[dest_size + src_size] = NULL;

	// Update the destination array pointer
	free(dest);  // Free the old array if it was dynamically allocated
	// *dest = new_dest;
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
	return (gb_add(ft_substr(str, start, *i - start)));
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
	// ret_str = ft_strdup("");
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
	// return (ret_str);
}

char	*handle_dollar(char *str, int *i, t_minishell *vars)
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
