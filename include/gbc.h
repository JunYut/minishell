/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: we <we@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:03:14 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/05 11:56:13 by we               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GBC_H
# define GBC_H

# include <stdlib.h>
# include "libft.h"
# include "define.h"

void	gbc_clear(void);
void	*gbc_malloc(size_t size);
t_gbc	*gbc_collector(void);
void	gbc_init(t_gbc *collector);
void	*gbc_add(void *addr);

#endif
