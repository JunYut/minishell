/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:29:31 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/16 09:00:09 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include "readline.h"
# include "history.h"
# include "libft.h"
# include "define.h"
# include "gbc.h"
# include "lexer.h"
# include "parser.h"
# include "expand.h"
# include "wildcard.h"
# include "signals.h"
# include "utils.h"

extern volatile sig_atomic_t	g_wait;

t_minishell	*init_vars(char *name, char **envp);
int			process_line(t_minishell *vars);
int			init_prompt(t_minishell *vars);
void		setup_terminal(t_minishell *vars);

int			exec_pipeline(t_node *node, t_minishell *vars);
void		exec_pipe_child(t_node *node, int *fd, int direction,
				t_minishell *vars);
int			exec_node(t_node *node, bool piped, t_minishell *vars);
int			exec_child(t_node *node, t_minishell *vars);
int			exec_subshell(t_node *subshell_node, t_minishell *vars);
int			exec_simple_cmd(t_node *node, bool piped, t_minishell *vars);
int			exec_builtin(char **args, int status, t_minishell *vars);
int			redir_out(t_io_node *io_list, int *status);
int			redir_in(t_io_node *io_list, int *status);
int			redir_append(t_io_node *io_list, int *status);
int			set_shlvl(t_minishell *vars);
void		ft_reset_stds(bool piped, t_minishell *vars);
int			wait_status(pid_t pid);
t_path		get_path(char *cmd, t_minishell *vars);
bool		is_valid_path(char **envp);
int			get_err_msg(t_err err);
t_err		check_exec(char *file);
int			check_redir(t_node *node);

int			builtin_export(char **ent, t_env *e);
int			export(char *key, char *val, t_env *e);
char		*fetch_val(char *key, t_env *e);
void		set_val(t_env *e, char *key, char *val);
char		**split_ent(char *str);
void		sort_export(t_var *exp);

int			builtin_cd(char **path, t_env *e);
char		*set_target(char **path, t_env *e);
int			count_args(char **path, char *func);

int			builtin_unset(char **keys, t_env *e);
void		rm_ent(char *key, t_var *lst, int last_id);

int			builtin_echo(char **av);

int			builtin_pwd(t_env *e);

void		exit_shell(char **argv, int status, t_minishell *vars);
int			clear(t_minishell *vars);

int			valid_key(char *key);
int			is_numeric(char *str);
bool		is_builtin(char *cmd);

#endif
