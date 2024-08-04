# Operating System
OS = $(shell uname)

# Compile & Flags
LEAKS = 0
CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99

ifeq ($(LEAKS), 1)
	CFLAGS += -fsanitize=address -g3
endif

# Directories
LIBFT_DIR = libft_module
MODULE_DIRS = append_module env_module gb_collect_module heredoc_module pipe_module redin_module redout_module signal_module
OBJ_DIR = obj
INCL_DIRS = $(addprefix -I, $(MODULE_DIRS)) -I$(LIBFT_DIR)/include -I.
LINK_DIRS = -L$(LIBFT_DIR)

vpath %.c $(MODULE_DIRS) # specify which directories the source files are located

# Files
SRCS = $(foreach dir, $(MODULE_DIRS), $(wildcard $(dir)/*.c))
OBJS = $(foreach src, $(SRCS), $(OBJ_DIR)/$(notdir $(src:.c=.o)))
HEADERS = $(foreach dir, $(MODULE_DIRS), $(wildcard $(dir)/*.h)) \
		  $(wildcard $(LIBFT_DIR)/include/*.h)
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -lft -lreadline
EXEC = exec

# Rules & Recipes
all : $(EXEC)

$(EXEC) : $(OBJS) $(LIBFT) main.c
	$(CC) $(CFLAGS) $(INCL_DIRS) $(OBJS) main.c $(LINK_DIRS) $(LIBS) -o $@

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o : %.c $(HEADERS)
	@echo  echo: $<
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCL_DIRS) -c $< -o $@

memcheck : all
ifeq ($(OS), Linux)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)
else
	leaks -atExit -- ./$(EXEC)
endif

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(EXEC)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all memcheck clean fclean re