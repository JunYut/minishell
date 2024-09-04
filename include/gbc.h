/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:03:14 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/04 09:40:24 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GBC_H
# define GBC_H

# include <stdlib.h>
# include "libft.h"
# include "define.h"

void	gb_clear(void);
void	*gb_malloc(size_t size);
void	gb_free(void *addr);
t_gbc	*gb_collector(void);
void	gb_init(t_gbc *collector);
void	*gb_add(void *addr);

#endif
