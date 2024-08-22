#!/bin/bash

OS=$(uname)
CFLAGS="-Wall -Wextra -Werror -Wpedantic"
INCL="-I../libft_module/include -I../include"
OBJS="../obj/*.o"
LIBS="-L../libft_module -lft"

# Input validation
if [ "$#" -lt 1 ]; then
	echo "Usage: sh $0 <file.c> [args]"
	exit 1
fi
if [ ! -f "$1" ]; then
	echo "File not found: $1"
	exit 1
fi

# Compile
make -C ..
if [ "$#" -eq 1 ] || [ "$2" = "-l" ]; then
	clang $CFLAGS $INCL $OBJS $1 $LIBS
elif [ "$2" = "-f" ]; then
	clang $CFLAGS-fsanitize=address $INCL  -g3 $OBJS $1 $LIBS
elif [ "$2" = "-g" ]; then
	clang $CFLAGS -g $INCL $OBJS $1 $LIBS
fi

# Run
if [ "$#" -eq 1 ]; then
	./a.out
elif [ "$2" = '-l' ]; then
	if [ "$OS" = 'Darwin' ]; then
		leaks -atExit -- ./a.out
	else
		valgrind --leak-check=full --show-leak-kinds=all ./a.out
	fi
fi