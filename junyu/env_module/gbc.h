# pragma once

# include <stdlib.h>
# include <stdio.h>

typedef struct s_gbc
{
	int				id;
	void			*addr;
	struct s_gbc	*next;
}	t_gbc;

void	gb_clear(void);
void	*gb_malloc(size_t size);
void	*gb_add(void *addr);
void	gb_init(t_gbc *collector);
t_gbc	*gb_collector(void);
