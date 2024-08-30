# include "env.h"

int	echo(char **av)
{
	int	nl;
	int	i;

	nl = 1;
	if (av && av[0])
	{
		if (ft_strcmp(av[0], "-n") == 0)
		{
			nl = 0;
			av++;
		}
		i = -1;
		while (av[++i])
		{
			printf("%s", av[i]);
			if (av[i + 1])
				printf(" ");
		}
	}
	if (nl)
		printf("\n");
	return (0);
}
