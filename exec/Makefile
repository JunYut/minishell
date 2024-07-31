# Operating System
OS = $(shell uname)

# Compile & Flags
LEAKS = 0
CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c89

ifeq ($(LEAKS), 1)
	CFLAGS += -fsanitize=address -g3
endif

# Directories
LIBFT_DIR = libft_module
APPD_DIR = append_module
ENV_DIR = env_module
HDOC_DIR = heredoc_module
PIPE_DIR = pipe_module
REDIN_DIR = redin_module
REDOUT_DIR = redout_module
SIG_DIR = signal_module
OBJ_DIR = obj
INCL_DIR = $(LIBFT_DIR)/include -I$(APPD_DIR) -I$(ENV_DIR) -I$(HDOC_DIR) \
		   -I$(PIPE_DIR) -I$(REDIN_DIR) -I$(REDOUT_DIR) -I$(SIG_DIR)

# Files
SRC = $(wildcard *.c)

# Rules & Recipes
all : 