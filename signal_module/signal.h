# pragma once

/*
Allowed functions:  signal, sigaction, sigemptyset, sigaddset

Non-interactive mode:
- ctrl-C displays '^C' then a new prompt on a new line.
- ctrl-D does nothing (no need to implement this).
- ctrl-\ displays '^\Quit: 3' then a new prompt on a new line.

Interactive mode(involves real-time user input):
- ctrl-C displays a new prompt on a new line.
- ctrl-D exits interactive mode. (no need to implement this)
- ctrl-\ does nothing.

Interactive actions: read, <<heredoc
*/

# include <signal.h>
# include <unistd.h>
