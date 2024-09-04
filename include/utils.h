/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 09:57:24 by tjun-yu           #+#    #+#             */
/*   Updated: 2024/09/04 10:46:41 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <errno.h>
# include <stdio.h>
# include "define.h"
# include "libft.h"
# include "gbc.h"

int			print_builtin_err(char *builtin, char *cause, char *error);
int			print_err(char *cause, char *error);

t_wc_type	*gb_newtoken(t_wc_type token);
t_list		*gb_lstnew(void *content);
char		*gb_itoa(int n);
char		*gb_strdup(const char *s1);

int			find_pos(char *str, char delim);
char		*ft_strndup(char *str, int pos);
void		ft_strncpy(char *dst, char *src, int len);


# endif
