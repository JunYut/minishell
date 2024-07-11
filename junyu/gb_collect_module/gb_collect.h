# pragma once

# include <stdlib.h>
# include <stdio.h>

typedef struct s_gb_collect {
	void			*addr;
	s_gb_collect	*next;
}	t_gb_collect;

void	gb_init(t_gb_collect *collector);
void	gb_clear(t_gb_collect **collector);
void	*gb_malloc(t_gb_collect *collector, size_t size);
void	gb_free(t_gb_collect *collector, void *addr);
