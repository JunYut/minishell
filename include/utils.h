/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:57:24 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/17 11:07:45 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include "define.h"
# include "libft.h"
# include "gbc.h"

int			print_builtin_err(char *builtin, char *cause, char *error);
int			print_err(char *cause, char *error);

t_wc_type	*gbc_newtoken(t_wc_type token);
t_list		*gbc_lstnew(void *content);
char		*gbc_itoa(int n);
char		*gbc_strdup(const char *s1);

char		**insert_string_array(char **dest, char **src, int insert_index);
char		**insert(char **dest, char **src, int insert_index);
int			count_strings(char **array);
int			find_pos(char *str, char delim);
char		*ft_strndup(char *str, int pos);
void		ft_strncpy(char *dst, char *src, int len);
int			is_space(char c);
int			is_quote(char c);
int			is_seperator(char *s);
void		skip_spaces(char **line);

void		show_tree(t_node *node, int depth, char *branch);
void		print_tree(t_node *node, int depth, char *branch);
void		print_arr(char **arr);
char		*get_node_type(int type);

void		ft_free(void **addr);

#endif
