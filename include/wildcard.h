/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:03 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/28 11:32:27 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "minishell.h"
# include "libft.h"
# include "define.h"
# include "gbc.h"

# ifndef DPRINTF
	# define DPRINTF(...) printf(__VA_ARGS__)
# endif

char		**wildcard(char *regex, t_env *env);
t_list		*ent_match(t_wildcard *wc, char *regex);
char		*pattern_match(char *ent, t_wc_type *token, char **pattern);
char		*r_strnstr(char *haystack, char *needle, size_t len);
t_wc_type	*tokenize_wc(char *regex);
t_dirent	*init_dirent(char *cwd);
int			count_token(char *regex);
void		sort_lex(t_list *lst);
void		lstswap(t_list *a, t_list *b);
char		**lst_to_arr(t_list *lst);
