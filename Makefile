# CFlags
CFLAGS = -Wall -Wextra -Werror -pedantic

# Directories
BUILTIN_DIR = builtins
OBJ_DIR = obj
INCL_DIR = include

# Files
SRC = $(wildcard $(BUILTIN_DIR)/*.c)
OBJ = $(SRC:$(BUILTIN_DIR)/%.c=$(OBJ_DIR)/%.o)
EXEC = shell

# Rules
all: $(EXEC)

$(EXEC): $(OBJ) main.c
	$(CC) $(CFLAGS) -I$(INCL_DIR) -o $@ $^

$(OBJ_DIR)/%.o: $(BUILTIN_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCL_DIR) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean

re: fclean all
