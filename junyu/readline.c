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

	The add_history() function adds the specified line to the history list. The
	history list is a list of lines that the user has entered using readline().

	The history list is a global linked list that is accessible to all functions
	in the Readline library. If the list is full, the oldest line will be removed
	to make room for the new line.

	Note: the history list is stored in memory and is not saved to disk
*/

/*
	void rl_clear_history(void)

	The rl_clear_history() function clears the history list. The history list is
	is a global linked list that is accessible to all functions in the Readline
	library.
*/

/*
	int rl_on_new_line(void)

	int: 0 if successful, -1 if error

	The rl_on_new_line() function is called when the user presses the Enter key.
	It is used to reset the Readline state so that the next line of text can be
	read.

	TLDR: use when using other Readline functions to manipulate the line of input.
		  Not necessary when using readline() by itself.
*/

/*
	rl_replace_line(const char *, int)

	const char *: the new line to display
	int: 1 if the line should be displayed, 0 if not

	The rl_replace_line() function replaces the current line of text with the
	specified line. If the second argument is 1, the new line will be displayed.

	!!! does not work on my machine
*/

/*
	void rl_redisplay(void)

	!!! does not work on my machine
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
		printf("You entered: %s\n", line);
		add_history(line);
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}
		free(line);
	}
	rl_clear_history();

	return 0;
}
