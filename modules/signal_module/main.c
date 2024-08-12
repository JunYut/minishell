#include "signal.h"
#include <readline/readline.h>
#include <stdio.h>

#define MODE 2

void handle_sigint(int sig) {
	(void)sig;
	printf("%d: Caught SIGINT\n", sig);
}

void handle_sigquit(int sig) {
	(void)sig;
	printf("%d: Caught SIGQUIT\n", sig);
}

int main() {

	printf("PID: %d\n", getpid());
	printf ("SIGINT: %d\n", SIGINT);
	printf ("SIGQUIT: %d\n", SIGQUIT);

	// Non-interactive mode
	#if MODE == 1
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);

		while (1)
			pause();
	#endif

	// Interactive mode
	#if MODE == 2
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);

		while (1)
			readline("> ");
	#endif

	return 0;
}
