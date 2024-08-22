# include "gbc.h"

t_list	*gb_lstnew(void *content)
{
	return (gb_add(ft_lstnew(content)));
}

char	*gb_strdup(const char *s1)
{
	return (gb_add(ft_strdup(s1)));
}
