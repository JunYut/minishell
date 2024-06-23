/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:22 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/06/23 23:53:20 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	main(void)
{
	t_minishell	g_minishell;

	while (1)
	{
		g_minishell.line = readline("minishell> ");
		if (g_minishell.line == NULL)
			break ;
		if (*g_minishell.line != '\0')
			add_history(g_minishell.line);
	}
	return (0);
}

void	tokenize(char *line)
{
	t_token	*token_list;

	token_list = NULL;
	while (*line != '\0')
	{
		if (!ft_strncmp(line, "<", 1))
			append_token(line, &token_list);
	}
}

void	append_token(char *line, t_token **token_list)
{
	t_token	*token

	token =
}

t_token	*init_new_token(char *value, t_token_type type)
{
	t_token *token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

//TODO: Implement function to append tokens to list
//TODO: Test and implement function for assigning token types
