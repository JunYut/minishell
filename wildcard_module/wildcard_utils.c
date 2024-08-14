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
