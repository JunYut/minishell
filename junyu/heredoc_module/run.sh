#!/bin/zsh

OS=$(uname)
CFLAGS="-Wall -Wextra -Werror -Wpedantic"
LIBS="-lreadline"

# Compile
if [ $# -eq 0 ] || [ "$1" = "-l" ]; then
	clang $CFLAGS *.c $LIBS
elif [ "$1" = "-f" ]; then
	clang $CFLAGS -fsanitize=address -g3 *.c $LIBS
elif [ "$1" = "-g" ]; then
	clang $CFLAGS -g *.c $LIBS
fi

# Run
if [ "$1" = "-l" ]; then
	if [ "$OS" = "Darwin" ]; then
		leaks -atExit -- ./a.out
	else
		valgrind --leak-check=full ./a.out
	fi
else
	./a.out
fi
