# pragma once

# include <stdlib.h>
# include <stdio.h>

typedef struct s_gbc {
	int				index;
	void			*addr;
	struct s_gbc	*next;
}	t_gbc;

void	*gb_malloc(t_gbc *collector, size_t size);
void	gb_free(t_gbc *collector);
void	gb_init(t_gbc *collector);
