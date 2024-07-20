/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:54:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/18 15:20:41 by kkhai-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gbc.h"

void	gb_clear(void)
{
	t_gbc	*current;
	t_gbc	*next;

	current = gb_collector();
	while (current)
	{
		free(current->addr);
		next = current->next;
		if (current->id != 0)
			free(current);
		current = next;
	}
}

void	*gb_malloc(size_t size)
{
	void	*addr;
	t_gbc 	*current;

	addr = malloc(size);
	current = gb_collector();
	while (current->next)
		current = current->next;
	current->addr = addr;
	current->next = malloc(sizeof(t_gbc));
	gb_init(current->next);
	return (addr);
}

void	gb_free(void *addr)
{
	t_gbc	*current;

	current = gb_collector();
	while (current)
	{
		if (current->addr == addr)
		{
			free(current->addr);
			current->addr = NULL;
			break ;
		}
		current = current->next;
	}
}

t_gbc	*gb_collector(void)
{
	static t_gbc	collector;

	return (&collector);
}

void	gb_init(t_gbc *collector)
{
	collector->addr = NULL;
	collector->next = NULL;
}

void	*gb_add(void *addr)
{
	t_gbc	*current;

	current = gb_collector();
	while (current->next)
		current = current->next;
	current->addr = addr;
	current->next = malloc(sizeof(t_gbc));
	gb_init(current->next);
	return (addr);
}
