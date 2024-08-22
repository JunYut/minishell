/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:06:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/22 15:14:23 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "gbc.h"
# include "define.h"
# include "lexer.h"
# include "parser.h"
# include "../libft/include/libft.h"

void	init_vars(t_minishell *vars, char **envp);

void	expand_tree(t_node *node, int depth, char *branch);
void	expand_node(t_node *node);
char	**expand_args(char *args);
char	*expand_params(char	*str);
char	*handle_squote(char *str, int *i);
char	*handle_dquote(char *str, int *i);
char	*handle_reg_str(char *str, int *i);
char	*handle_dollar(char *str, int *i);
bool	is_valid_var_char(char c);

t_env	*dup_env(char **envp);
void	env(t_env *e, char lst);
void	unset(char **keys, t_env *v);
void	add_ent(t_env *e, char *key, char *val);
int		find_pos(char *str, char delim);
char	**split_ent(char *str);
char	*ft_strndup(char *str, int pos);
void	set_val(t_env *e, char *key, char *val);
// int		ft_strcmp(char *s1, char *s2);
void	ft_strncpy(char *dst, char *src, int len);
char	*fetch_val(char *key, t_env *e);

void	append(char *file, char *cmd, char *args[]);
void	write_file(char *file, char *content);
char	*read_pipe(int read_fd);
void	append_str(char **str1, char *str2);

char	*parse_path(char *envp[], char *cmd);
void	trim_path(char *cmd, char *path);
void	prepend_cmd(char **path_list, char *cmd);

char	*remove_quotes(char *str);
// int	unquoted_strlen(char *str, char quotes);

char	**split_args(char *str);
int		count_words(char *str);
void	skip_word(char *str, int *i);
char	**allocate_args(char *str, char **args);
char	**fill_args(char *str, char **args);
void	fill_word(char *str, char **args, int *i, int j);

// void	append_str(char **str1, char *str2);
void	heredoc(t_io_node *io, int *p_fd);
char	*read_doc(char *delimiter);

// int	exec_node(t_node *node, bool piped, t_minishell *vars);


#endif
