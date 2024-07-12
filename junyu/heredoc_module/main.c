# include "heredoc.h"

# define TEST 1

int main(void)
{
	# if TEST == 0
	char	*cmd = NULL;
	char	*args[] = {NULL};
	# endif
	# if TEST == 0
	char	*cmd = "/usr/bin/cat";
	char	*args[] = {"cat", "-e", NULL};
	# endif

	// heredoc(cmd, args, "eof");
	// printf("[%s]\n", readline("> "));
}
