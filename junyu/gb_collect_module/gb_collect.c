# include "gb_collect.h"

void	gb_init(t_gb_collect *collector)
{
	collector->addr = NULL;
	collector->next = NULL;
	collector->next = gb_malloc(collector, sizeof(t_gb_collect));
}

void	gb_clear(t_gb_collect **collector)
{

}

void	*gb_malloc(t_gb_collect *collector, size_t size)
{
	void	*addr;
	t_gb_collect *current;

	addr = malloc(size);
	if (!addr)
	{
		perror("malloc");
		return (NULL);
	}
	current = collector;
	while (current->next)
		current = current->next;
	current->addr = addr;
	current->next = NULL;
	return (addr);
}

void	gb_free(t_gb_collect *collector, void *addr);