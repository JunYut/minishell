/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:11 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/06/28 01:07:20 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define OPERATORS_SET "|><()"

typedef enum e_token_type
{
	T_WORD,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_HERE_DOC,
	T_APPEND,
	T_PIPE,
	T_L_BRACKET,
	T_R_BRACKET,
	T_OR,
	T_AND,
	T_NEWLINE,
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

extern t_minishell	g_minishell;

void	tokenize(char *line);
void	append_operator_token(t_token_type type, char **line, t_token **token_list);
void	handle_operator_token(char **line, t_token **list);
// void	append_identifier_token(t_token_type type, char **line, t_token **token_list);
void	append_word_token(char **line, t_token **token_list);
t_token	*init_new_token(t_token_type type, char *value);
void	add_token_to_list(t_token **token_list, t_token *token);
int	is_space(char c);
int	is_seperator(char c);
void	skip_spaces(char **line);
int	is_in_set(char c, char *set);
int	is_quote_closed(char *line, int	*i);
int	is_quote(char c);

#endif

// TODO: Split header into their respective files
