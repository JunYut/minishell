# pragma once

# define DEBUG 0
# define EXPORT 1
# define VAR 2
# define READ_SIZE 42

# if DEBUG
	# define DPRINTF printf
# else
	# define DPRINTF(...) do {} while (0)
# endif
