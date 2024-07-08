#!/bin/zsh

OS=$(uname)
CFLAGS="-Wall -Wextra -Werror -Wpedantic"
LIBS="-lreadline -ltermcap -lcurses"

# Input validation
if [ $# -lt 1 ]; then
	echo "Usage: sh $0 <file.c> [args]"
	exit 1
fi
if [ ! -f $1 ]; then
	echo "File not found: $1"
	exit 1
fi

# Compile
if [ $# -eq 1 ]; then
	clang $CFLAGS $1 $LIBS
elif [ $2 = "-f" ]; then
	clang $CFLAGS -fsanitize=address -g3 $1 $LIBS
elif [ $2 = "-g" ]; then
	clang $CFLAGS -g $1 $LIBS
fi

# Run
if [ $# -eq 1 ]; then
	./a.out
elif [ $2 == '-l' ]; then
	if [ $OS == "Darwin" ]; then
		leaks -atExit -- ./a.out
	else
		valgrind --leak-check=full ./a.out
	fi
fi