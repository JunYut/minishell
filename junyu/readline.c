/*
	char *readline(const char *)

	char *: the line read from the user
	const char *: the prompt to display

	When readline() is called, it will display the prompt to the user and wait 
	for the user to enter a line of text. The line of text is then returned to 
	the caller.

	If the user presses Ctrl-D, readline() will return NULL. If the user presses
	Ctrl-C, readline() will return NULL and set errno to EINTR.

	If the user presses the up arrow key, the previous line of text will be
	displayed. If the user presses the down arrow key, the next line of text will
	be displayed.
	Note: the return value must be freed by the caller
*/

/*
	int add_history(const char *)

	int: 0 if successful, -1 if error
	const char *: the line to add to the history list
*/

/*

*/

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>

int main(void)
{
	char *line;

	while (1)
	{
		line = readline("Enter a line: ");
		add_history(line);
		free(line);
	}
	rl_clear_history();
}
