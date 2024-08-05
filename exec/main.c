# include "redir.h"
# include "libft.h"
# include "gbc.h"

# define TEST 1

int main(void)
{
	# if TEST == 1
	char	*cmd = NULL;
	char	*args[] = {NULL};
	# endif
	# if TEST == 0
	char	*cmd = "/usr/bin/cat";
	char	*args[] = {"cat", "-e", NULL};
	# endif

	heredoc("eof", cmd, args);
	// printf("[%s]\n", readline("> "));
}
