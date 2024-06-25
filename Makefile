# CFlags
CFLAGS = -Wall -Wextra -Werror -pedantic

# Directories
LIBFT_DIR = libft
BUILTIN_DIR = builtins
OBJ_DIR = obj
INCL_DIR = include -Ilibft/include

# Files
SRC = $(wildcard $(BUILTIN_DIR)/*.c)
OBJ = $(SRC:$(BUILTIN_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT = $(LIBFT_DIR)/libft.a
LIB = ft -lreadline
EXEC = shell

# Rules
all: $(EXEC)

$(EXEC): $(LIBFT) $(OBJ) main.c
	$(CC) $(CFLAGS) -I$(INCL_DIR) $^ -L$(LIBFT_DIR) -l$(LIB) -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(BUILTIN_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCL_DIR) -c -o $@ $<

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(EXEC)
	make -C $(LIBFT_DIR) fclean

re: fclean all
