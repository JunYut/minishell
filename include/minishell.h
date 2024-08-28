/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:06:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/28 11:58:58 by kkhai-ki         ###   ########.fr       */
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
# include "gbc.h"
# include "define.h"
# include "lexer.h"
# include "parser.h"
# include "expand.h"
# include "wildcard.h"
# include "../libft/include/libft.h"

void	init_vars(t_minishell *vars, char **envp);

int	exec_node(t_node *node, bool piped, t_minishell *vars);
t_path	get_path(char *cmd, t_minishell *vars);
int	exec_child(t_node *node, t_minishell *vars);
int	exec_simple_cmd(t_node *node, bool piped, t_minishell *vars);
int	check_redir(t_node *node);
int	redir_out(t_io_node *io_list, int *status);
int	redir_in(t_io_node *io_list, int *status);
int	redir_append(t_io_node *io_list, int *status);

int		exec_pipeline(t_node *node, t_minishell *vars);
void	exec_pipe_child(t_node *node, int *fd, int direction, t_minishell *vars);
int		get_exit_status(int status);
int		get_err_msg(t_err err);

void	print_arr(char **arr);

#endif
