NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
REMOVE = rm -rf

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = include

HEADERS	= -I ./include

SRC = $(wildcard $(SRC_PATH)/*.c)
OBJ = $(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

ORANGE = \033[1;38;5;208m
RESET = \033[0m
U_LINE = \033[4m
YELLOW = \033[1;38;5;226m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(HEADERS) -o $@
	@echo "\n$(ORANGE)$(U_LINE)⭐️ $(NAME): Compiled ⭐️$(RESET) \n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "$(YELLOW)$(NAME) Compiling:$(RESET) $(notdir $<)"

clean:
	@$(REMOVE) $(OBJ_PATH)

fclean: clean
	@$(REMOVE) $(NAME)

re: fclean all

.PHONY: all clean fclean re
