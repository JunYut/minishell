# include "redout.h"

# define TEST 1

int main(void)
{
	# if TEST == 0
	char *file = "output.txt";
	char *cmd = "/usr/bin/ls";
	char *args[] = { "ls", "-lh", NULL };
	# endif
	# if TEST == 0
	char *file = "output.txt";
	char *cmd = "/usr/bin/echo";
	char *args[] = { "echo", "Hello world !", NULL };
	# endif
	# if TEST == 1
	char *file = "output.txt";
	char *cmd = "/usr/bin/ps";
	char *args[] = { "ps", NULL };
	# endif

	append(file, cmd, args);
}
