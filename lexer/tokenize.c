/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:22 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/17 17:32:48 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			break	;
		}
		skip_spaces(&line);
		if (!ft_strncmp(line, "&&", 2) || is_in_set(*line, OPERATORS_SET))
			token_err = handle_operator_token(&line, &token_list);
		else
			token_err = append_word_token(&line, &token_list, vars);
		// printf("Line: %s\n", line);
	}
	vars->token_list = token_list;
}

bool	handle_operator_token(char **line, t_token **token_list)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (append_operator_token(T_HERE_DOC, line, token_list));
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

bool	append_operator_token(t_token_type type, char **line, t_token **token_list)
{
	t_token	*token;
	char	*value;
	int		char_count;

	char_count = 1;
	if (type == T_HERE_DOC || type == T_APPEND || type == T_OR || type == T_AND)
		char_count++;
	value = ft_substr(*line, 0, char_count);
	if (!value)
		return (true);
	token = init_new_token(type, value);
	if (!token)
		return (true);
	add_token_to_list(token_list, token);
	*line += char_count;
	return (false);
}

bool	append_word_token(char **line, t_token **token_list, t_minishell *vars)
{
	t_token	*token;
	char	*value;
	int		char_count;
	char	*buffer;

	if (!vars)
		return (0);
	buffer = *line;
	char_count = 0;
	while (buffer[char_count] && !is_seperator(buffer + char_count))
	{
		if (is_quote(buffer[char_count]))
		{
			if (is_quote_closed(buffer, &char_count) == false)
			{
				handle_open_quote(&(*line), &buffer, &char_count, buffer[char_count]);
				break ;
			}
		}
		else
			char_count++;
	}
	value = ft_substr(buffer, 0, char_count);
	if (!value)
		return (true);
	token = init_new_token(T_WORD, value);
	if (!token)
		return (free(value), true);
	*line += char_count;
	add_token_to_list(token_list, token);
	return (false);
}

//NOTES: When encountering multiple syntax errors, Bash will report the first one
//NOTES: We can tokenize first then validate or validate sequentially
//NOTES: Multiple string literals without any seperators that are not in quotes in-between are considered 1 token only e.g. "ls""-l" is treated as ls-l

//TODO: move error handling for quotes to parser
//TODO: handle open quotes or brackets
