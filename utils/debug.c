# include "debug.h"

void	print_token(t_token *token, char **pattern)
{
	int		i;
	int		j;

	j = 0;
	i = -1;
	while (token[++i] != T_END)
	{
		if (token[i] == T_WILDCARD)
			DPRINTF("*");
		else
			DPRINTF("[%s]", pattern[j++]);
		if (token[i + 1] != T_END)
			DPRINTF(" ");
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
		DPRINTF("[%s]\n", (char *)curr->content);
		curr = curr->next;
	}
}
