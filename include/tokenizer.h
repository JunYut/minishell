/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:11 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/06/23 17:06:01 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "../libft/include/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type
{
	T_WORD,
	T_RED_IN,
	T_RED_OUT,
	T_HERE_DOC,
	T_APPEND,
	T_PIPE,
	T_L_BRACKET,
	T_R_BRACKET,
	T_OR,
	T_AND,
	T_NL,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_minishell
{
	t_token	*token_list;
	char	*line;
}	t_minishell;

extern t_minishell g_minishell;

#endif

// TODO: Split header into their respective files
