/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:22 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/24 14:59:46 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "gbc.h"

void	tokenize(char *line, t_minishell *vars)
{
	t_token	*token_list;
	int		i;
	bool	token_err;

	token_list = NULL;
	token_err = false;
	i = 0;
	while (line[i] != '\0')
	{
		if (token_err == true)
		{
			clear_token_list(&token_list);
			break ;
		}
		skip_spaces(line, &i);
		if (line[i] == '\0')
			break ;
		if (!ft_strncmp(line + i, "&&", 2) || is_in_set(line[i], OPERATORS_SET))
			token_err = handle_operator_token(line, &i, &token_list);
		else
			token_err = append_word_token(&line, &i, &token_list, vars);
	}
	free(line);
	vars->token_list = token_list;
}

bool	handle_operator_token(char *line, int *i, t_token **token_list)
{
	line += *i;
	if (!ft_strncmp(line, "<<", 2))
		return (append_operator_token(T_HEREDOC, line, i, token_list));
	else if (!ft_strncmp(line, ">>", 2))
		return (append_operator_token(T_APPEND, line, i, token_list));
	else if (!ft_strncmp(line, "<", 1))
		return (append_operator_token(T_REDIRECT_IN, line, i, token_list));
	else if (!ft_strncmp(line, ">", 1))
		return (append_operator_token(T_REDIRECT_OUT, line, i, token_list));
	else if (!ft_strncmp(line, "||", 2))
		return (append_operator_token(T_OR, line, i, token_list));
	else if (!ft_strncmp(line, "|", 1))
		return (append_operator_token(T_PIPE, line, i, token_list));
	else if (!ft_strncmp(line, "&&", 1))
		return (append_operator_token(T_AND, line, i, token_list));
	else if (!ft_strncmp(line, "(", 1))
		return (append_operator_token(T_L_BRACKET, line, i, token_list));
	else
		return (append_operator_token(T_R_BRACKET, line, i, token_list));
}

bool	append_operator_token(t_token_type type, char *line, int *i,
		t_token **lst)
{
	t_token	*token;
	char	*value;
	int		count;

	count = 1;
	if (type == T_HEREDOC || type == T_APPEND || type == T_OR || type == T_AND)
		count++;
	value = ft_substr(line, 0, count);
	if (!value)
		return (true);
	token = init_new_token(type, value);
	if (!token)
		return (free(value), true);
	add_token_to_list(lst, token);
	*i += count;
	return (false);
}

bool	append_word_token(char **line, int *i, t_token **lst, t_minishell *vars)
{
	int		count;
	char	*buffer;
	bool	error;

	if (!vars)
		return (0);
	buffer = ft_strdup(*line + *i);
	count = 0;
	while (buffer[count] && !is_seperator(buffer + count))
	{
		if (is_quote(buffer[count]))
		{
			if (is_quote_balance(buffer + count, buffer[count]) == true)
				skip_quote_string(buffer, &count);
			else
			{
				handle_open_quote(line, &buffer, i, &count);
				break ;
			}
		}
		else
			count++;
	}
	error = init_word_token(line, buffer, count, lst);
	return (*i += count, free(buffer), error);
}

bool	init_word_token(char **line, char *buffer, int count, t_token **lst)
{
	char	*value;
	t_token	*token;

	(void)line;
	value = ft_substr(buffer, 0, count);
	if (!value)
		return (true);
	token = init_new_token(T_WORD, value);
	if (!token)
		return (free(value), true);
	add_token_to_list(lst, token);
	return (false);
}
