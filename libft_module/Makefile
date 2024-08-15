# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: we <we@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 17:12:39 by kkhai-ki          #+#    #+#              #
#    Updated: 2024/08/15 14:49:37 by we               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
ORANGE = \033[0;38;5;166m

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDE = -Iinclude

SRC_DIR = src
SRC_FILES =	ft_isalpha			\
			ft_isdigit			\
			ft_isalnum			\
			ft_isascii			\
			ft_isprint			\
			ft_strlen			\
			ft_memset			\
			ft_bzero			\
			ft_memcpy			\
			ft_memmove			\
			ft_strlcpy			\
			ft_strlcat			\
			ft_toupper			\
			ft_tolower			\
			ft_strchr			\
			ft_strrchr			\
			ft_strcmp			\
			ft_strncmp			\
			ft_swap				\
			ft_memchr			\
			ft_memcmp			\
			ft_strnstr			\
			ft_atoi				\
			ft_atol				\
			ft_calloc			\
			ft_strdup			\
			ft_substr			\
			ft_strjoin			\
			ft_strtrim			\
			ft_split			\
			ft_itoa				\
			ft_strmapi			\
			ft_striteri			\
			ft_putchar_fd		\
			ft_putstr_fd		\
			ft_putendl_fd		\
			ft_putnbr_fd		\
			ft_lstnew			\
			ft_lstadd_front		\
			ft_lstsize			\
			ft_lstlast			\
			ft_lstadd_back		\
			ft_lstdelone		\
			ft_lstclear			\
			ft_lstiter			\
			ft_lstmap			\
			ft_find_len			\
			ft_print_char		\
			ft_print_hex		\
			ft_print_nbr		\
			ft_print_ptr		\
			ft_print_str		\
			ft_print_unsigned	\
			ft_flags			\
			ft_parse_flags		\
			ft_printf			\
			get_next_line_utils	\
			get_next_line		\
			ft_free_s_arr		\
			ft_atoi_base

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC_FILES)))

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SRC_FILES)))

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) :	$(OBJ_DIR) $(OBJ)
			@echo "$(GREEN)Object files created.$(RESET)"
			@ar rcs $@ $(OBJ) && echo "$(GREEN)libft.a created.$(RESET)"

$(OBJ_DIR) :
			@mkdir -p $(OBJ_DIR)

all :		$(NAME)

clean :
			@rm -rf $(OBJ_DIR) && echo "$(RED)Object files deleted.$(RESET)"

fclean:		clean
			@rm -rf $(NAME) && echo "$(RED)libft.a deleted.$(RESET)"

re:			fclean all
