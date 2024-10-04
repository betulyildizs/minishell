NAME = minishell
SRC = parser/tokenizer.c minishell.c
OBJ := $(SRC:.c=.o)
CFLAGS = #-Wall -Wextra -Werror
CC = gcc

LIB_DIR = lib
LIB_NAME = readline-8.2
LIB_ARCHIVE = $(LIB_NAME).tar.gz
LIB_URL = https://ftp.gnu.org/gnu/readline/$(LIB_ARCHIVE)
LIB_BUILD_DIR = $(LIB_DIR)/$(LIB_NAME)/build

# libft ayarları
LIBFT_DIR = lib/libft
LIBFT_MAKEFILE = $(LIBFT_DIR)/Makefile

all: $(LIB_BUILD_DIR) libft $(NAME)

$(LIB_BUILD_DIR):
	@mkdir -p $(LIB_DIR)
	@curl -L $(LIB_URL) -o $(LIB_DIR)/$(LIB_ARCHIVE)
	@tar -xzf $(LIB_DIR)/$(LIB_ARCHIVE) -C $(LIB_DIR)
	@cd $(LIB_DIR)/$(LIB_NAME) && ./configure --prefix=$(PWD)/$(LIB_BUILD_DIR)
	@make -C $(LIB_DIR)/$(LIB_NAME)
	@make -C $(LIB_DIR)/$(LIB_NAME) install

libft:
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIB_BUILD_DIR) libft
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(LIB_BUILD_DIR)/lib -I$(LIB_BUILD_DIR)/include -lreadline -L$(LIBFT_DIR) -lft

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(LIB_BUILD_DIR)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: re fclean clean all libft
