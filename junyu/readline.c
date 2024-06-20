/*
	char *readline(const char *)

	char *: the line read from the user
	const char *: the prompt to display to the user

	Need to include <readline/readline.h>
	Need to link with -lreadline
	Need to free the line after using it
*/

# include <readline/readline.h>
# include <stdio.h>

int main(void)
{
	char *line;

	while (1)
	{
		line = readline("Enter a line: ");
		printf("You entered: %s\n", line);
		free(line);
	}
}
