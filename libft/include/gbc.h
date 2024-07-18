#ifndef GBC_H
# define GBC_H

# include <stdlib.h>

typedef struct s_gbc
{
	int				id;
	void			*addr;
	struct s_gbc	*next;
}	t_gbc;

void	gb_clear(void);
void	*gb_malloc(size_t size);
void	gb_free(void *addr);
t_gbc	*gb_collector(void);
void	gb_init(t_gbc *collector);

#endif
