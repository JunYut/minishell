/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:22 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/06/26 18:29:21 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
t_minishell g_minishell;

int	main(void)
{
	g_minishell.token_list = NULL;
	g_minishell.line = NULL;
	while (1)
	{
		g_minishell.line = readline("minishell> ");
		if (g_minishell.line == NULL)
			break ;
		if (*g_minishell.line != '\0')
			add_history(g_minishell.line);
		tokenize(g_minishell.line);
		if (g_minishell.token_list == NULL)
			continue ;
		while (g_minishell.token_list != NULL)
		{
			printf("value: %s\n", g_minishell.token_list->value);
			printf("type: %d\n", g_minishell.token_list->type);
			g_minishell.token_list = g_minishell.token_list->next;
		}
	}
	return (0);
}

void	tokenize(char *line)
{
	t_token	*token_list;

	token_list = NULL;
	while (*line != '\0')
	{
		skip_spaces(&line);
		// if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
		// 	|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
		// 	|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
		if (!ft_strncmp(line, "&&", 2) || is_in_set(*line, OPERATORS_SET))
			handle_operator_token(&line, &token_list);
		else
			line++;
	}
	g_minishell.token_list = token_list;
}

void	handle_operator_token(char **line, t_token **token_list)
{
		if (!ft_strncmp(*line, "<<", 2))
			append_operator_token(T_HERE_DOC, line, token_list);
		else if (!ft_strncmp(*line, ">>", 2))
			append_operator_token(T_APPEND, line, token_list);
		else if (!ft_strncmp(*line, "<", 1))
			append_operator_token(T_REDIRECT_IN, line, token_list);
		else if (!ft_strncmp(*line, ">", 1))
			append_operator_token(T_REDIRECT_OUT, line, token_list);
		else if (!ft_strncmp(*line, "||", 2))
			append_operator_token(T_OR, line, token_list);
		else if (!ft_strncmp(*line, "|", 1))
			append_operator_token(T_PIPE, line, token_list);
		else if (!ft_strncmp(*line, "&&", 1))
			append_operator_token(T_AND, line, token_list);
		else if (!ft_strncmp(*line, "(", 1))
			append_operator_token(T_L_BRACKET, line, token_list);
		else
			append_operator_token(T_R_BRACKET, line, token_list);
}


void	append_operator_token(t_token_type type, char **line, t_token **token_list)
{
	t_token	*token;
	char	*value;
	int		char_count;

	char_count = 1;
	if (type == T_HERE_DOC || type == T_APPEND || type == T_OR || type == T_AND)
		char_count++;
	value = ft_substr(*line, 0, char_count);
	token = init_new_token(type, value);
	add_token_to_list(token_list, token);
	*line += char_count;
}

// void	append_identifier_token(t_token_type type, char **line, t_token **token_list)
// {
// 	t_token	*token;
// 	char	*value;
// 	int		char_count;

// }

t_token	*init_new_token(t_token_type type, char *value)
{
	t_token *token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token_to_list(t_token **token_list, t_token *token)
{
	t_token	*current;

	if (*token_list == NULL)
	{
		*token_list = token;
		return	;
	}
	current = *token_list;
	while (current != NULL && current->next != NULL)
		current = current->next;
	current->next = token;
	token->prev = current;
}

//TODO: Finish functions for appending tokens to list
//TODO: Test and implement function for assigning token types
//TODO: Implement utility functions for managing linked lists

//NOTES: When encountering multiple syntax errors, Bash will report the first one
//NOTES: We can tokenize first then validate or validate sequentially
