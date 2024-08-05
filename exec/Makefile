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
MODULES_DIR = env_module gb_collect_module pipe_module redir_module signal_module
OBJ_DIR = obj
INCL_DIR = $(foreach module, $(MODULES_DIR), $(addprefix -I, $(module))) \
		   -I$(LIBFT_DIR)/include -I.

vpath %.c $(MODULES_DIR)

# Files
SRC = $(foreach module, $(MODULES_DIR), $(wildcard $(module)/*.c))
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
HEADER = $(foreach module, $(MODULES_DIR), $(wildcard $(module)/*.h)) \
		 $(wildcard $(LIBFT_DIR)/include/*.h) *.h
LIBFT = $(LIBFT_DIR)/libft.a
LIB = -L$(LIBFT_DIR) -lft -lreadline
EXEC = exec

# Rules & Recipes
all : $(EXEC)

$(EXEC) : $(OBJ) $(LIBFT) main.c
	$(CC) $(CFLAGS) $(INCL_DIR) $(OBJ) main.c $(LIB) -o $@

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o : %.c $(HEADER)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCL_DIR) -c $< -o $@

run : $(EXEC)
	./$(EXEC)

memcheck : CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99
memcheck :
	make all
ifeq ($(OS), Linux)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)
else
	leaks --atExit -- ./$(EXEC)
endif

clean :
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -rf $(EXEC)
	$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all run memcheck clean fclean re