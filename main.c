# include "builtins.h"

int main(void)
{
	// cd()
	// char buf[1024];

	// getcwd(buf, 1024);
	// printf("Before: %s\n", buf);
	// cd(NULL);
	// getcwd(buf, 1024);
	// printf("After: %s\n", buf);

	// echo()
	const char *const argv[] = {"-n", "Hello", "World", NULL};
	echo(NULL);

	(void)argv;
}
