/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:06:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/29 16:13:49 by we               ###   ########.fr       */
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

extern volatile __sig_atomic_t	g_wait;

void	init_vars(t_minishell *vars, char **envp);

int		exec_node(t_node *node, bool piped, t_minishell *vars);
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

void	print_arr(char **arr);

#endif
