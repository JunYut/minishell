# include "redin.h"
# include <string.h>
# include <stdio.h>

# define DEBUG 1
# define TEST 1

int main(void)
{
	# if TEST == 1
	char *cmd = "/bin/cat";
	char *file = "run.sh";
	char *argv[] = {"cat", "-e", NULL};
	# endif

	redin(file, cmd, argv);

	# if DEBUG == 0
	while (1);
	# endif
}
