/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:34:11 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/15 09:04:32 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#define FAIL 0
#define SUCCESS 1

t_node	*parse(t_minishell *vars);
t_node	*get_term(t_minishell *vars);
t_node	*get_simple_cmd(t_minishell *vars);
bool	join_args(t_minishell *vars, char **args);
bool	get_io_list(t_minishell *vars, t_io_node **io_list);
t_node	*get_expression(t_minishell *vars, int min_prec);
void	set_parse_err_type(t_minishell *vars, t_parse_err_type type);
bool	is_logic_op_or_pipe(t_token *token);
int	token_precedence(t_token_type type);
bool	is_redirection(t_token_type type);
t_io_type	get_io_type(t_token_type type);
t_node	*init_new_node(t_node_type type);
t_io_node	*init_new_io_node(t_token_type type, char *value);
t_node *build_operator_node(t_minishell *vars, t_token_type token_type, t_node *left, t_node *right);
void	clear_cmd_node(t_node *node);
void	recursive_clear_ast(t_node *node);
void	clear_ast(t_token **token_list, t_node **ast);
void	clear_io_list(t_io_node **list);
void	append_io_node(t_io_node **list, t_io_node *new_node);
void	handle_parse_error(t_minishell *vars);

#endif