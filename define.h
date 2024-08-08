# pragma once

# define DEBUG 1
# define EXPORT 1
# define VAR 2
# define READ_SIZE 42

# if DEBUG == 1
	# define DPRINTF printf
	# define DPRINT_ARR(arr) print_arr(arr)
# else
	# define DPRINTF(...) do {} while (0)
	# define DPRINT_ARR(...) do {} while (0)
# endif
