# pragma once

# define READ_SIZE 1024
# define DEBUG 0
# define EXPORT 1
# define VAR 2

# if DEBUG
	# define DPRINTF printf
# else
		# define DPRINTF(...) do {} while (0)
# endif
