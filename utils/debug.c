# include "debug.h"

void	print_token(t_list *token, char **pattern)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = token;
	while (curr)
	{
		if (*(t_token *)curr->content == T_WILDCARD)
			DPRINTF("*");
		else
			DPRINTF("%s", pattern[i++]);
		if (curr->next)
			DPRINTF(" ");
		curr = curr->next;
	}
	DPRINTF("\n");
}

void	print_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		DPRINTF("%s\n", arr[i]);
}

void	print_lst(t_list *lst)
{
	t_list	*curr;

	curr = lst;
	while (curr)
	{
		DPRINTF("%s\n", (char *)curr->content);
		curr = curr->next;
	}
}
