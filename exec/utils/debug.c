# include "utils.h"

int	print_arr(char **arr)
{
	int	i;

	if (arr == NULL)
		return (-1);
	i = -1;
	while (arr[++i] != NULL)
		printf("%s ", arr[i]);
	printf("\n");
	return (0);
}
