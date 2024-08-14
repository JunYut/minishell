# include "wildcard.h"

# define TEST 1

int main(void)
{
	# if TEST == 1
	char	*regex = "*";
	# endif

	print_arr(wildcard(regex));

	gb_clear();
}
