/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:03 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/09 12:24:48 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include <dirent.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "define.h"
# include "gbc.h"

// # ifndef DPRINTF
// 	# define DPRINTF(...) printf(__VA_ARGS__)
// # endif

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

#endif
