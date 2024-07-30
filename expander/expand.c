/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:29:42 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/30 13:31:52 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_tree(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->type ==  N_PIPE || node->type == N_AND || node->type == N_OR)
	{
		expand_tree(node->left);
		expand_tree(node->right);
	}
	expand_node(node);
}

void	expand_node(t_node *node)
{
	t_io_node	*io;

	if (node->args)
		node->exp_args = expand_args(node->args);
	io = node->io_list;
	while (io != NULL)
	{
		io = io->next;
	}
}

char	**expand_args(char *args)
{
	char	**expanded;
	char	*buffer;
	int		i;

	(void)expanded;
	(void)i;

	buffer = expand_params(args);
	printf("expanded: %s\n", buffer);
	return (NULL);
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
	char	*quote_str;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	quote_str = ft_substr(str, start, *i - start);
	return (quote_str);
}

char	*handle_dquote(char *str, int *i)
{
	int		start;
	char	*quote_str;

	start = *i;
	(*i)++;
	while (str[*i] != '"')
		(*i)++;
	(*i)++;
	quote_str = ft_substr(str, start, *i - start);
	return (quote_str);
}
