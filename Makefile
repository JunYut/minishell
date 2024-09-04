# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjun-yu <tjun-yu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:33:10 by kkhai-ki          #+#    #+#              #
#    Updated: 2024/09/04 09:30:04 by tjun-yu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# COLORS
GREEN	= \033[0;32m
RED		= \033[0;31m
RESET	= \033[0m
ORANGE	= \033[0;38;5;166m

# Compiler & Flags
CC		= clang
CFLAGS	= -Wall -Wextra -Werror -Wpedantic -g

# Directories
RL_DIR		= readline
LIBFT_DIR	= libft
MODULES_DIR	= executor expander gbc lexer parser wildcard builtins utils
OBJ_DIR		= obj
INCL_DIR	= -Iinclude -I$(RL_DIR) -I$(LIBFT_DIR)/include

vpath %.c $(MODULES_DIR)

# Files
SRC			= $(foreach module, $(MODULES_DIR), $(wildcard $(module)/*.c)) signals.c
OBJ			= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
HEADER		= include/*.h $(wildcard $(RL_DIR)/*.h) \
				$(wildcard $(LIBFT_DIR)/include/*.h)
READLINE	= $(RL_DIR)/libreadline.a $(RL_DIR)/libhistory.a
LIBFT		= $(LIBFT_DIR)/libft.a
LIB			= -L$(RL_DIR) -L$(LIBFT_DIR) -lft -lreadline -lncurses
EXEC		= minishell

# Debug
# $(info SRC: $(SRC))
# $(info OBJ: $(OBJ))
# $(info HEADER: $(HEADER))
# $(info INCL_DIR: $(INCL_DIR))

# Rules & Recipes
all : $(EXEC)

$(EXEC) : $(READLINE) $(LIBFT) $(OBJ) main.c
	$(CC) $(CFLAGS) $(INCL_DIR) $(OBJ) main.c $(LIB) -o $@

$(READLINE) :
	cd $(RL_DIR) && ./configure && make
	cd ..

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o : %.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCL_DIR) -c $< -o $@

run : $(EXEC)
	./$(EXEC)

memcheck :
	$(MAKE) re
ifeq ($(shell uname), Linux)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXEC)
else
	leaks --atExit -- ./$(EXEC)
endif

fsan :
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address -g3" re
	$(MAKE) run

clean :
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(RL_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -rf $(EXEC)
	$(MAKE) -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all run memcheck clean fclean re
