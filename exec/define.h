# pragma once

# include <signal.h>

# define DEBUG 1
# define EXPORT 1
# define VAR 2
# define READ_SIZE 42

typedef enum e_token
{
	T_CMD,
	T_REDIN,
	T_REDOUT,
	T_HERE_DOC,
	T_APPEND,
	T_PIPE,
	T_PIPE_START,
	T_PIPE_END,
	T_OR,
	T_AND,
	T_END,
	T_INVALID = -1
}	t_token;

volatile sig_atomic_t	g_wait;

# if DEBUG == 1
	# define DPRINTF printf
	# define DPRINT_ARR(arr) print_arr(arr)
	# define NL printf("\n")
# else
	# define DPRINTF(...) do {} while (0)
	# define DPRINT_ARR(...) do {} while (0)
# endif
