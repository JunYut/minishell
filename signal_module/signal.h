# pragma once

/*
Allowed functinos:  signal, sigaction, sigemptyset, sigaddset

Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
In interactive mode:
- ctrl-C displays a new prompt on a new line.
- ctrl-D exits the shell.
- ctrl-\ does nothing.
*/

# include <signal.h>
