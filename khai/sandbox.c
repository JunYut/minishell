#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	while (1)
	{
		char	*str;

		str = readline("minishell> ");
		if (str == NULL)
			break ;
		add_history(str);
	}
	return (0);
}
