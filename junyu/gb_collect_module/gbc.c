# include "gbc.h"

void	gb_clear(t_gbc *collector)
{
	t_gbc	*current;
	t_gbc	*next;

	current = collector;
	while (current)
	{
		free(current->addr);
		next = current->next;
		if (current->id != 0)
			free(current);
		current = next;
	}
}

void	*gb_malloc(t_gbc *collector, size_t size)
{
	void	*addr;
	t_gbc *current;

	addr = malloc(size);
	current = collector;
	while (current->next)
		current = current->next;
	current->addr = addr;
	current->next = malloc(sizeof(t_gbc));
	gb_init(current->next);
	return (addr);
}

void	gb_free(t_gbc *collector, void *addr)
{
	t_gbc	*current;

	current = collector;
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
