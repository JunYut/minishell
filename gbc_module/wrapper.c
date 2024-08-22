# include "gbc.h"

t_list	*gb_lstnew(void *content)
{
	return (gb_add(ft_lstnew(content)));
}

char	*gb_strdup(const char *s1)
{
	return (gb_add(ft_strdup(s1)));
}

t_token	*gb_newtoken(t_token token)
{
	t_token	*new;

	new = gb_malloc(sizeof(t_token));
	*new = token;
	return (new);
}
