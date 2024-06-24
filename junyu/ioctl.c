/*
	int ioctl(int, unsigned long, ...)

	int: 0 or positive indicates success, -1 indicates failure
	int: file descriptor of the device
	unsigned long: request
	...: depends on the request code can be used to pass & return data to/from the
		 device driver

	Use to manipulate the underlying device parameters of special files
*/

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
	struct winsize w;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
		perror("ioctl");
		return 1;
	} else {
		printf("Width: %d, Height: %d\n", w.ws_col, w.ws_row);
	}
	return 0;
}
