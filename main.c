# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int main(void)
{
	execve("/bin/ls", NULL, NULL);
}