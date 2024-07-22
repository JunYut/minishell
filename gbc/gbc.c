/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:54:54 by kkhai-ki          #+#    #+#             */
/*   Updated: 2024/07/22 12:26:45 by kkhai-ki         ###   ########.fr       */
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
		free(current);
		current = next;
	}
	free(current);
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
	static t_gbc	*collector;

	if (collector == NULL)
	{
		collector = malloc(sizeof(t_gbc));
		gb_init(collector);
	}
	return (collector);
}

void	gb_init(t_gbc *collector)
{
	if (collector != NULL)
	{
		collector->addr = NULL;
		collector->next = NULL;
	}
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
