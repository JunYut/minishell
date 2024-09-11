/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:22 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/11 21:11:58 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "gbc.h"

void	tokenize(char *line, t_minishell *vars)
{
	t_token	*token_list;
	bool	token_err;

	token_list = NULL;
	token_err = false;
	while (*line != '\0')
	{
		if (token_err == true)
		{
			clear_token_list(&token_list);
			break ;
		}
		skip_spaces(&line);
		if (!ft_strncmp(line, "&&", 2) || is_in_set(*line, OPERATORS_SET))
			token_err = handle_operator_token(&line, &token_list);
		else
			token_err = append_word_token(&line, &token_list, vars);
	}
	vars->token_list = token_list;
}

bool	handle_operator_token(char **line, t_token **token_list)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (append_operator_token(T_HEREDOC, line, token_list));
	else if (!ft_strncmp(*line, ">>", 2))
		return (append_operator_token(T_APPEND, line, token_list));
	else if (!ft_strncmp(*line, "<", 1))
		return (append_operator_token(T_REDIRECT_IN, line, token_list));
	else if (!ft_strncmp(*line, ">", 1))
		return (append_operator_token(T_REDIRECT_OUT, line, token_list));
	else if (!ft_strncmp(*line, "||", 2))
		return (append_operator_token(T_OR, line, token_list));
	else if (!ft_strncmp(*line, "|", 1))
		return (append_operator_token(T_PIPE, line, token_list));
	else if (!ft_strncmp(*line, "&&", 1))
		return (append_operator_token(T_AND, line, token_list));
	else if (!ft_strncmp(*line, "(", 1))
		return (append_operator_token(T_L_BRACKET, line, token_list));
	else
		return (append_operator_token(T_R_BRACKET, line, token_list));
}

bool	append_operator_token(t_token_type type, char **line, t_token **lst)
{
	t_token	*token;
	char	*value;
	int		count;

	count = 1;
	if (type == T_HEREDOC || type == T_APPEND || type == T_OR || type == T_AND)
		count++;
	value = ft_substr(*line, 0, count);
	if (!value)
		return (true);
	token = init_new_token(type, value);
	if (!token)
		return (free(value), true);
	add_token_to_list(lst, token);
	*line += count;
	return (false);
}

bool	append_word_token(char **line, t_token **token_list, t_minishell *vars)
{
	int		count;
	char	*buffer;
	bool	error;

	if (!vars)
		return (0);
	buffer = *line;
	count = 0;
	while (buffer[count] && !is_seperator(buffer + count))
	{
		if (is_quote(buffer[count]))
		{
			if (is_quote_balance(buffer + count, buffer[count]) == true)
				skip_quote_string(buffer, &count);
			else
			{
				handle_open_quote(&(*line), &buffer, &count, buffer[count]);
				break ;
			}
		}
		else
			count++;
	}
	error = init_word_token(line, buffer, count, token_list);
	return (error);
}

bool	init_word_token(char **line, char *buffer, int count, t_token **lst)
{
	char	*value;
	t_token	*token;

	value = ft_substr(buffer, 0, count);
	if (!value)
		return (true);
	token = init_new_token(T_WORD, value);
	if (!token)
		return (free(value), true);
	*line += count;
	add_token_to_list(lst, token);
	return (false);
}
