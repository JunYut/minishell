# include "gbc.h"

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

void	gb_free(t_gbc *collector)
{
	t_gbc	*current;
	t_gbc	*next;

	current = collector;
	while (current)
	{
		free(current->addr);
		next = current->next;
		if (current->index != 0)
			free(current);
		current = next;
	}
}

void	gb_init(t_gbc *collector)
{
	static int	index;

	collector->index = index++;
	collector->addr = NULL;
	collector->next = NULL;
}
