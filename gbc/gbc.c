/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:54:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/09/10 15:17:38 by tjun-yu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gbc.h"

void	gbc_clear(void)
{
	t_gbc	*current;
	t_gbc	*next;

	current = gbc_collector();
	while (current)
	{
		free(current->addr);
		current->addr = NULL;
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
}

void	*gbc_malloc(size_t size)
{
	void	*addr;
	t_gbc	*current;

	addr = malloc(size);
	current = gbc_collector();
	while (current->next)
		current = current->next;
	current->addr = addr;
	current->next = malloc(sizeof(t_gbc));
	gbc_init(current->next);
	return (addr);
}

t_gbc	*gbc_collector(void)
{
	static t_gbc	*collector;

	if (collector == NULL)
	{
		collector = malloc(sizeof(t_gbc));
		gbc_init(collector);
	}
	return (collector);
}

void	gbc_init(t_gbc *collector)
{
	if (collector != NULL)
	{
		collector->addr = NULL;
		collector->next = NULL;
	}
}

void	*gbc_add(void *addr)
{
	t_gbc	*current;

	current = gbc_collector();
	while (current->next)
		current = current->next;
	current->addr = addr;
	current->next = malloc(sizeof(t_gbc));
	gbc_init(current->next);
	return (addr);
}
