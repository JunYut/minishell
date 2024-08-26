# include "gbc.h"

void	gb_clear()
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
void    *gb_add(void *addr)
{
    t_gbc    *current;

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

void	gb_init(t_gbc *collector)
{
	static int	id;

	collector->id = id++;
	collector->addr = NULL;
	collector->next = NULL;
}

// ** mind_explode.gif *
t_gbc	*gb_collector(void)
{
	static t_gbc	*collector;

	if (!collector)
	{
		collector = malloc(sizeof(t_gbc));
		gb_init(collector);
	}
	return (collector);
}
