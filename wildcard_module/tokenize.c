# include "wildcard.h"

t_list	*tokenize(char *str)
{
	t_list	*token;
	int		i;

	token = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '*')
		{
			ft_lstadd_back(&token, gb_lstnew(gb_newtoken(T_WILDCARD)));
			while (str[i + 1] && str[i + 1] == '*')
				++i;
		}
		else
		{
			ft_lstadd_back(&token, gb_lstnew(gb_newtoken(T_PATTERN)));
			while (str[i + 1] && str[i + 1] != '*')
				++i;
		}
	}
	return (token);
}
