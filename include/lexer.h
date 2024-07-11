/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:11 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/11 15:33:20 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define OPERATORS_SET "|><()"

bool	append_operator_token(t_token_type type, char **line, t_token **token_list);
bool	handle_operator_token(char **line, t_token **list);
t_token	*init_new_token(t_token_type type, char *value);
void	add_token_to_list(t_token **token_list, t_token *token);
int	is_space(char c);
int	is_seperator(char *s);
void	skip_spaces(char **line);
int	is_in_set(char c, char *set);
int	is_quote_closed(char *line, int	*i);
int	is_quote(char c);
void	clear_token_list(t_token **token_list);
void	tokenize(char *line, t_minishell *vars);
void	handle_quote_err(char quote, t_minishell *vars);
bool	append_word_token(char **line, t_token **token_list, t_minishell *vars);

#endif

// TODO: Split header into their respective files
