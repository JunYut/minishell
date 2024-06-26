# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:33:10 by kkhai-ki          #+#    #+#              #
#    Updated: 2024/06/26 17:57:20 by kkhai-ki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
ORANGE = \033[0;38;5;166m

CC = gcc
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address -g3

INCLUDE = -Iinclude -I$(LIBFT_DIR)

SRC_DIR = tokenizer

SRC_FILES =	main	\
			utils

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBRARIES = -L$(LIBFT_DIR) -lft -lreadline

all :
		@mkdir -p $(OBJ_DIR)
		@make -C libft
		@make $(NAME)

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) :	$(OBJ)
			@printf "$(GREEN)minishell object files created.$(RESET)\n"
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBRARIES) && echo "$(GREEN)minishell created.$(RESET)"

clean :
			@rm -rf $(OBJ_DIR) && echo "$(RED)minishell object files deleted.$(RESET)"
			@make clean -C $(LIBFT_DIR)

fclean:
			@rm -rf $(OBJ_DIR) $(NAME) && echo "$(RED)minishell deleted.$(RESET)"
			@rm -rf $(OBJ_DIR) && echo "$(RED)minishell object files deleted.$(RESET)"
			@make fclean -C $(LIBFT_DIR)

re:			fclean all

.PHONY:	clean fclean re all

# TODO: Clean up Makefile and change structure
