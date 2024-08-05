/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:06:58 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/05 12:24:04 by kkhai-ki         ###   ########.fr       */
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

void	init_vars(t_minishell *vars);

void	expand_tree(t_node *node);
void	expand_node(t_node *node);
char	**expand_args(char *args);
char	*expand_params(char	*str);
char	*handle_squote(char *str, int *i);
char	*handle_dquote(char *str, int *i);
char	*handle_reg_str(char *str, int *i);

void	append(char *file, char *cmd, char *args[]);
void	write_file(char *file, char *content);
char	*read_pipe(int read_fd);
void	append_str(char **str1, char *str2);

char	*parse_path(char *envp[], char *cmd);
void	trim_path(char *cmd, char *path);
void	prepend_cmd(char **path_list, char *cmd);

#endif
