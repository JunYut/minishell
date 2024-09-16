/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:31:48 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/16 11:59:35 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include "readline.h"
# include "define.h"
# include "gbc.h"

int		init_heredocs(t_node *node, t_minishell *vars);
int		heredoc_child(t_io_node *io, int *p_fd, pid_t pid, t_minishell *vars);
void	expand_node(t_node *node, t_minishell *vars);
char	**expand_args(char *args, t_minishell *vars);
char	*expand_params(char	*str, t_minishell *vars);
char	*handle_squote(char *str, int *i);
char	*handle_dquote(char *str, int *i, t_minishell *vars);
char	*handle_reg_str(char *str, int *i);
char	*handle_dollar(char *str, int *i, t_minishell *vars);
bool	is_valid_var_char(char c);
bool	is_valid_regex(char *str);
t_env	*dup_env(char *envp[]);
int		builtin_env(t_env *e, char lst);
int		builtin_unset(char **keys, t_env *v);
void	add_ent(t_env *e, char *key, char *val);
char	**split_ent(char *str);
void	set_val(t_env *e, char *key, char *val);
char	*fetch_val(char *key, t_env *e);
char	**env_to_arr(t_var *var);

void	append(char *file, char *cmd, char *args[]);
void	write_file(char *file, char *content);
char	*read_pipe(int read_fd);
void	append_str(char **str1, char *str2);

char	*parse_path(char *envp[], char *cmd);
void	trim_path(char *cmd, char *path);
void	prepend_cmd(char **path_list, char *cmd);

char	**split_args(char *str);
int		count_words(char *str);
void	skip_word(char *str, int *i);
char	**allocate_args(char *str, char **args);
char	**fill_args(char *str, char **args);
void	fill_word(char *str, char **args, int *i, int j);

void	heredoc(t_io_node *io, int *p_fd, t_minishell *vars);
char	*read_doc(char *delimiter, t_minishell *vars);
char	*expand_heredoc(char *line, t_minishell *vars);
char	*handle_non_var(char *line, int *i);

char	*remove_outer_quotes(char *str);
int		find_result_len(char *input, int len);
char	*build_result_string(char *input, int len, int result_len);

#endif
