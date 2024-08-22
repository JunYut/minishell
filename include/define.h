# pragma once

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
	T_OR,
	T_AND,
	T_END,
	T_INVALID = -1
}	t_token;

# if DEBUG == 1
	# define DPRINTF printf
	# define DPRINT_ARR(arr) print_arr(arr)
	# define DPRINT_LST(lst) print_lst(lst)
	# define NEWLINE printf("\n")
# else
	# define DPRINTF(...) do {} while (0)
	# define DPRINT_ARR(...) do {} while (0)
# endif
