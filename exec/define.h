# pragma once

# define DEBUG 1
# define EXPORT 1
# define VAR 2
# define READ_SIZE 42

# if DEBUG == 1
	# define DPRINTF printf
# else
	# define DPRINTF(...) do {} while (0)
# endif
