# include "redin.h"
# include <stdio.h>

# define TEST 1

int main(void)
{
	# if TEST == 1
	char *cmd = "/bin/ls";
	char *file = "run.sh";
	char *argv[] = {"ls", "-l", NULL};
	# endif

}
