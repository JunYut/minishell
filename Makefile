# CFlags
CFLAGS = -Wall -Wextra -Werror -pedantic

# Directories
LIBFT_DIR = libft
BUILTIN_DIR = builtins
CMD_DIR = commands
OBJ_DIR = obj
INCL_DIR = include -Ilibft/include

# Files
SRC = $(wildcard $(BUILTIN_DIR)/*.c) \
	  $(wildcard $(CMD_DIR)/*.c)
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
HEADER = $(wildcard $(INCL_DIR)/*.h)
LIBFT = $(LIBFT_DIR)/libft.a
LIB = ft -lreadline
EXEC = shell

# Rules
all: $(EXEC)

$(EXEC): $(LIBFT) $(OBJ) main.c
	$(CC) $(CFLAGS) -I$(INCL_DIR) $^ -L$(LIBFT_DIR) -l$(LIB) -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(BUILTIN_DIR)/%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCL_DIR) -c -o $@ $<

$(OBJ_DIR)/%.o: $(CMD_DIR)/%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCL_DIR) -c -o $@ $<

clean:
#	@echo $(OBJ)
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(EXEC)
	make -C $(LIBFT_DIR) fclean

re: fclean all
