/*
	int tcsetattr(int fd, int optional_actions, const struct termios *termios_p)

	int: 0 indicates success, -1 indicates failure
	int: file descriptor of the device
	int: optional actions
	struct termios *: pointer to a termios structure that contains the new parameters
					  for the terminal

	optional_actions:
	- TCSANOW: changes occur immediately
	- TCSADRAIN: changes occur after all output written to the terminal has been transmitted
	- TCSAFLUSH: changes occur after all output written to the terminal has been transmitted,
				 and all input that has been received but not read will be discarded

	Used to set the terminal attributes
*/

/*
	int tcgetattr(int, struct termios *)

	int: 0 indicates success, -1 indicates failure
	int: file descriptor of the device
	struct termios *: pointer to a termios structure that will be filled with the current
					  terminal attributes

	Used to get the terminal attributes
*/

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int main() {
	struct termios term;
	int fd = STDIN_FILENO; // Standard input as the file descriptor

	// Get current terminal settings
	if (tcgetattr(fd, &term) == -1) {
		perror("tcgetattr");
		return 1;
	}
	printf("c_lflag: %lx\n", term.c_lflag);
	printf("c_iflag: %lx\n", term.c_iflag);
	printf("c_oflag: %lx\n", term.c_oflag);
	printf("c_cflag: %lx\n\n", term.c_cflag);

	// Modify settings: Disable canonical mode and echo
	term.c_lflag &= ~(ICANON | ECHO);

	// Apply the settings immediately
	if (tcsetattr(fd, TCSANOW, &term) == -1) {
		perror("tcsetattr");
		return 1;
	}
	printf("c_lflag: %lx\n", term.c_lflag);
	printf("c_iflag: %lx\n", term.c_iflag);
	printf("c_oflag: %lx\n", term.c_oflag);
	printf("c_cflag: %lx\n", term.c_cflag);

	// Your program logic here

	// Remember to restore the original settings before exiting
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &term);

	return 0;
}
