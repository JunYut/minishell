# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkhai-ki <kkhai-ki@student.42kl.edu.my>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 14:33:10 by kkhai-ki          #+#    #+#              #
#    Updated: 2024/07/01 13:49:35 by kkhai-ki         ###   ########.fr        #
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

INCLUDE = -Iinclude -I$(LIBFT_DIR) -I$(LIBFT_DIR)/include

TOKENIZER = tokenizer/main.c	\
			tokenizer/utils.c

PARSER = parser/parser.c

SRC =	$(TOKENIZER) $(PARSER)

OBJ_DIR = obj
OBJ = $(SRC:%.c=%.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBRARIES = -L$(LIBFT_DIR) -lft -lreadline

all :
		mkdir -p $(OBJ_DIR)
		make -C libft
		make $(NAME)

$(OBJ_DIR)/%.o:		$(SRC)%.c | $(OBJ_DIR)
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) :	$(OBJ)
			@printf "$(GREEN)minishell object files created.$(RESET)\n"
			$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME) $(LIBRARIES) && echo "$(GREEN)minishell created.$(RESET)"

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
