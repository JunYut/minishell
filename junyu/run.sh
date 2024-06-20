#!/bin/zsh

CFLAGS = -Wall -Wextra -Werror -Wpedantic

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
	gcc $CFLAGS $1
else if [ $2 = "-f" ]; then
	gcc $CFLAGS -fsanitize=address -g3 $1
else if [ $2 = "-g" ]; then
	gcc $CFLAGS -g $1
fi

# Run
if [ $2 = '-l']; then
	leaks -atExit -- ./a.out
else if [$2 = '-v']; then
	valgrind --leak-check=full ./a.out
else
	./a.out
fi
