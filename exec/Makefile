# Operating System
OS = $(shell uname)

# Compile & Flags
CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c89

LEAKS = 0

ifeq ($(LEAKS), 1)
	CFLAGS += -fsanitize=address -g3
endif