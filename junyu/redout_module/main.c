# include "redout.h"

# define TEST 1

int main(void)
{
	# if TEST == 1
	char *file = "output.txt";
	char *cmd = "/usr/bin/ls";
	char *args[] = { "ls", "-lh", NULL };
	# endif

	redout(file, cmd, args);
}
