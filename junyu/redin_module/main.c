# include "redin.h"
# include <string.h>
# include <stdio.h>

# define TEST 1

int main(void)
{
	# if TEST == 1
	// char *cmd = "/bin/ls";
	char *file = "run.sh";
	// char *argv[] = {"ls", "-l", NULL};
	# endif

	char *content = read_file(file);
	printf("content:\n[%s]\n", content);
	free(content);

	// char *str1 = strdup("hello");
	// append(&str1, " world");
	// printf("str1: [%s]\n", str1);
	// free(str1);
}
