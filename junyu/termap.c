/*
	char *getenv(const char *)

	char *: pointer to the value of the environment variable
	const char *: name of the environment variable
*/

/*
	int tgetent(char *bp, const char *name)

	int: 1 indicates success, 0 indicates terminal type not found, -1 indicates error
	char *: buffer to store the terminal description
	const char *: name of the terminal type

	Load the terminal description for the terminal type name into the buffer bp.
*/

/*
	int tgetflag(char *id)

	int: 1 if the terminal has the capability, 0 otherwise
	char *: capability name
*/

/*
	int tgetnum(char *id)

	int: the value of the capability, -1 if not defined
	char *: capability name
*/

/*
	char *tgetstr(char *id, char **area)

	char *: the escape sequence for the capability, NULL if not defined
	char *: capability name
	char **: pointer to the area to store the escape sequence
*/

/*
	char *tgoto(char *cap, int col, int row)

	char *: the escape sequence for the capability
	char *: capability name
	int: column number
	int: row number
*/

/*
	int tputs(const char *, int, int (*)(int))

	int: 0 if successful, -1 if error
	const char *: escape sequence
	int: number of lines affected
	int (*)(int): function to output the escape sequence

	Output the escape sequence to the terminal.
*/

#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	char termbuf[2048]; // Buffer for terminal description
	char *termtype = getenv("TERM"); // Get the terminal type

	if (termtype == NULL) {
		fprintf(stderr, "Environment variable TERM not set.\n");
		return EXIT_FAILURE;
	}

	// Load the terminal description
	int status = tgetent(termbuf, termtype);
	if (status == 0) {
		fprintf(stderr, "Terminal type '%s' is not defined in termcap database.\n", termtype);
		return EXIT_FAILURE;
	} else if (status < 0) {
		fprintf(stderr, "Could not access the termcap database.\n");
		return EXIT_FAILURE;
	}

	// If successful, you can now use other termcap functions to query terminal capabilities
	printf("Terminal type '%s' loaded successfully.\n", termtype);
	printf("Terminal description:[%s]\n", termbuf);

	// tgetflag()
	// Check if the terminal supports automatic margins
	int has_am = tgetflag("am");

	if (has_am) {
		printf("This terminal supports automatic margins.\n");
	} else {
		printf("This terminal does not support automatic margins.\n");
	}

	// tgetnum()
	// Query the number of columns (width) of the terminal
	int cols = tgetnum("co");

	if (cols != -1) {
		printf("The terminal has %d columns.\n", cols);
	} else {
		printf("The number of columns is not defined.\n");
	}

	// tgetstr()
	// Query the escape sequence to clear the screen
	// char *clear_screens = tgetstr("cl", NULL);

	// if (clear_screens != NULL) {
	// 	printf("The escape sequence to clear the screen is: [%s]\n", clear_screens);
	// } else {
	// 	printf("The escape sequence to clear the screen is not defined.\n");
	// }

	// tgoto()
	// char *cm = tgetstr("cm", NULL); // Get the cursor movement control string
	// if (cm != NULL) {
	// 	char *move_cursor = tgoto(cm, 100, 5); // Move cursor to column 10, row 5
	// 	printf("%s", move_cursor); // Execute the cursor movement
	// } else {
	// 	printf("The cursor movement control string is not defined.\n");
	// }

	// tputs()
	char *cm = tgetstr("cm", NULL); // Get the cursor movement control string
	if (cm != NULL) {
		tputs(cm, 1, putchar); // Move cursor to column 10, row 5
	} else {
		printf("The cursor movement control string is not defined.\n");
	}

	return EXIT_SUCCESS;
}
