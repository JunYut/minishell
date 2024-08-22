# include "debug.h"

void	print_token(t_list *token)
{
	t_list	*curr;

	curr = token;
	while (curr)
	{
		DPRINTF("%d\n", *(t_token *)curr->content);
		curr = curr->next;
	}
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
