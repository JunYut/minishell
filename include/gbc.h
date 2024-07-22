/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:03:14 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/22 12:03:47 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GBC_H
# define GBC_H

# include <stdlib.h>

typedef struct s_gbc
{
	void			*addr;
	struct s_gbc	*next;
}	t_gbc;

void	gb_clear(void);
void	*gb_malloc(size_t size);
void	gb_free(void *addr);
t_gbc	*gb_collector(void);
void	gb_init(t_gbc *collector);
void	*gb_add(void *addr);

#endif
