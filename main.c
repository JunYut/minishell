# include "builtins.h"

int main(void)
{
	execve("/bin/ls", NULL, NULL);
	cd("../");
}
