CC					= clang
CFLAGS			=
PROGRAM			= minishell
SRC_DIR			= src
BIN_DIR			= bin
INC_DIR			= -Iinc -I./lib/readline/include
OBJ_DIR			= build
NAME				= $(BIN_DIR)/$(PROGRAM)
SRCS				= src/main.c src/syntax_cont.c src/run_commands.c \
				src/run_env.c \

	

OBJS					= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
RM						= rm -rf
RLFLAGS				= -L./lib/readline/lib -I./lib/readline/include/readline -lreadline
DIR						= $(shell echo $(PWD))
READLINE			= ./lib/readline/lib/libreadline.a

w = 1
ifeq '$(w)' '1'
CFLAGS += -Wextra -Werror -Wall
endif

debug = 1
ifeq '$(debug)' '1'
CFLAGS += -g
endif

asan = 0
ifeq '$(asan)' '1'
CFLAGS += -fsanitize=address
endif

all: $(READLINE)
	@mkdir -p bin
	@$(MAKE) $(NAME)

$(READLINE):
	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz
	@tar -xvf readline-8.2-rc1.tar.gz
	@$(RM) readline-8.2-rc1.tar.gz
	@cd readline-8.2-rc1 && ./configure --prefix=$(DIR)/lib/readline && make && make install
	@$(RM) readline-8.2-rc1

$(NAME): $(OBJS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(RLFLAGS) $(INC_DIR) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
