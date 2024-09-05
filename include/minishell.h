/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/05 16:16:32 by we               ###   ########.fr       */
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
# include <dirent.h>
# include <errno.h>
# include "libft.h"
# include "define.h"
# include "gbc.h"
# include "lexer.h"
# include "parser.h"
# include "expand.h"
# include "wildcard.h"
# include "signals.h"
# include "utils.h"

extern volatile __sig_atomic_t	g_wait;

void	init_vars(t_minishell *vars, char **envp);

int		exec_node(t_node *node, bool piped, t_minishell *vars);
int		exec_subshell(t_node *subshell_node, t_minishell *vars);
t_path	get_path(char *cmd, t_minishell *vars);
int		exec_child(t_node *node, t_minishell *vars);
int		exec_simple_cmd(t_node *node, bool piped, t_minishell *vars);
int		check_redir(t_node *node);
int		redir_out(t_io_node *io_list, int *status);
int		redir_in(t_io_node *io_list, int *status);
int		redir_append(t_io_node *io_list, int *status);

int		exec_pipeline(t_node *node, t_minishell *vars);
void	exec_pipe_child(t_node *node, int *fd, int direction, t_minishell *vars);
int		wait_status(pid_t pid, t_env *e);
int		get_exit_status(int status);
int		get_err_msg(t_err err);

int		builtin_cd(char **path, t_env *e);
char	*set_target(char **path, t_env *e);
int		count_args(char **path, char *func, t_env *e);

int		builtin_echo(char **av);

int		builtin_export(char **ent, t_env *e);
int		export(char *key, char *val, t_env *e);
char	*fetch_val(char *key, t_env *e);
void	set_val(t_env *e, char *key, char *val);
char 	**split_ent(char *str);
void 	sort_export(t_var *exp);

int		valid_key(char *key, t_env *e);
int		builtin_unset(char **keys, t_env *e);
void	rm_ent(char *key, t_var *lst, int last_id);

int		builtin_pwd(t_env *e);\

void	exit_shell(char **status, t_env *e);
int		is_numeric(char *str);

#endif
