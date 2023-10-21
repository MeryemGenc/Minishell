export GNUMAKEFLAGS	= --no-print-directory

DEFAULT		= \033[0;39m
RED			= \033[0;91m
GREEN		= \033[0;92m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m

BIN			= bin/minishell
NAME		= $(BIN)

CC			= gcc -g
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRC_DIR		= src
UTIL_DIR	= src/utilities
OBJ_DIR		= obj
BIN_DIR		= bin
READL		= -L /usr/local/opt/readline/lib
READI		= -I /usr/local/opt/readline/include

SRC			= $(shell find src -type f -not -path "src/utilities/*" -name "*.c" | cut -sd / -f 2-)
UTILS		= $(shell find src/utilities -type f -name "*.c" | cut -c 15-)
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
UTIL_OBJ	= $(addprefix $(OBJ_DIR)/, $(UTILS:.c=.o))

all: $(NAME)

$(NAME): create_dirs $(OBJ) $(UTIL_OBJ)
	@$(CC) $(CFLAGS) $(READI) $(READL) $(OBJ) $(UTIL_OBJ) -lreadline -o $@
	@echo "$(MAGENTA)$(BIN) compiled!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(READI) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(UTIL_DIR)/%.c
	@$(CC) $(READI) $(CFLAGS) -c $< -o $@

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)$(BIN)$(BLUE) objects removed.$(GREEN)"; \
	else \
		echo "$(RED)$(BIN) objects already removed."; \
	fi

fclean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)$(BIN)$(BLUE) objects removed.$(GREEN)"; \
	else \
		echo "$(RED)$(BIN) objects already removed."; \
	fi
	@if [ -d "$(BIN_DIR)" ]; then \
		$(RM) -r $(BIN_DIR); \
		echo "$(RED)$(BIN)$(BLUE) binary removed.$(GREEN)"; \
	else \
		echo "$(RED)$(BIN) binary already removed."; \
	fi

re: fclean all

create_dirs:
	@if [ ! -d "$(OBJ_DIR)" ]; then \
		mkdir -p $(OBJ_DIR); \
		echo "$(BLUE)$(BIN) objects directory created."; \
	else \
		echo "$(RED)objects directory already exists."; \
	fi
	@if [ ! -d "$(BIN_DIR)" ]; then \
		mkdir -p $(BIN_DIR); \
		echo "$(BLUE)$(BIN) binary directory created."; \
	else \
		echo "$(RED)binary directory already exists."; \
	fi
	@echo "$(GREEN)$(BIN) compiling...";

.PHONY: all clean fclean re create_dirs