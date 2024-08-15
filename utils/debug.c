# include "wildcard.h"

void	print_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		DPRINTF("%s\n", arr[i]);
		i++;
	}
}

void	print_lst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		DPRINTF("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}
