# CFlags
CFLAGS = -Wall -Wextra -Werror -pedantic

# Directories
BUILTIN_DIR = builtin
OBJ_DIR = obj
INCL_DIR = include

# Files
SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
EXEC = shell

# Rules
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean

re: fclean all
