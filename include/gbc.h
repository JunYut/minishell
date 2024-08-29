/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:03:14 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/08/29 11:14:41 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GBC_H
# define GBC_H

# include <stdlib.h>
# include "libft.h"
# include "define.h"

void		gb_clear(void);
void		*gb_malloc(size_t size);
void		gb_free(void *addr);
t_gbc		*gb_collector(void);
void		gb_init(t_gbc *collector);
void		*gb_add(void *addr);

t_wc_type	*gb_newtoken(t_wc_type token);
t_list		*gb_lstnew(void *content);
char		*gb_strdup(const char *s1);

#endif
