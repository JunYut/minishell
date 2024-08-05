# include "redir.h"
# include "libft.h"
# include "gbc.h"

# define TEST 3

int main(void)
{
	// redin
	# if TEST == 1	
	char	*cmd = "/bin/cat";
	char	*args[] = {"cat", "-e", NULL};
	int		fd = open("input.txt", O_RDONLY);

	redin(fd, cmd, args);
	# endif

	// redout
	# if TEST == 2	
	char	*cmd = "/bin/echo";
	char	*args[] = {"echo", "Writing", "to", "output.txt...", NULL};
	int		fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	redout(fd, cmd, args);
	# endif

	// append
	# if TEST == 3
	char	*cmd = "/bin/echo";	
	char	*args[] = {"echo", "Appending", "to", "output.txt...", NULL};
	int		fd = open("output.txt", O_APPEND | O_WRONLY | O_CREAT, 0644);

	redout(fd, cmd, args);
	# endif
	
	// heredoc
	# if TEST == 4	
	char	*cmd = "/bin/cat";
	char	*args[] = {"cat", "-e", NULL};

	heredoc("eof", cmd, args);
	# endif

	gb_clear();
}
