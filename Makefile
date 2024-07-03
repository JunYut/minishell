# CFlags
CFLAGS = -Wall -Wextra -Werror -pedantic

ifdef D
	CFLAGS += -fsanitize=address -g3
endif

# Directories
LIBFT_DIR = libft
BUILTIN_DIR = builtins
TOKEN_DIR = tokenizer
PARSE_DIR = parser
CMD_DIR = commands
EXEC_DIR = executor
OBJ_DIR = obj
INCL_DIR = -Iinclude -Ilibft/include

# Files
SRC = $(wildcard $(BUILTIN_DIR)/*.c) \
	  $(wildcard $(TOKEN_DIR)/*.c) \
	  $(wildcard $(PARSE_DIR)/*.c) \
	  $(wildcard $(CMD_DIR)/*.c) \
	  $(wildcard $(EXEC_DIR)/*.c)
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
HEADER = $(wildcard $(INCL_DIR)/*.h)
LIBFT = $(LIBFT_DIR)/libft.a
LIB = -lft -lreadline
EXEC = shell

# Rules
all: $(EXEC)

$(EXEC): $(LIBFT) $(OBJ) main.c
	cc $(CFLAGS) $(INCL_DIR) $(OBJ) main.c -L$(LIBFT_DIR) $(LIB) -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(BUILTIN_DIR)/%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCL_DIR) -c -o $@ $<

$(OBJ_DIR)/%.o: $(TOKEN_DIR)/%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCL_DIR) -c -o $@ $<

$(OBJ_DIR)/%.o: $(PARSE_DIR)/%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCL_DIR) -c -o $@ $<

$(OBJ_DIR)/%.o: $(CMD_DIR)/%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCL_DIR) -c -o $@ $<

$(OBJ_DIR)/%.o: $(EXEC_DIR)/%.c $(HEADER)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCL_DIR) -c -o $@ $<

clean:
#	@echo $(OBJ)
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(EXEC)
	make -C $(LIBFT_DIR) fclean

re: clean fclean all
