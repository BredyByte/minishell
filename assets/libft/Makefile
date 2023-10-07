NAME = libft.a

CC = cc
CFLAGS =  -Wall -Wextra -Werror
ARFLAGS = ar -rcs
REMOVE = rm -rf

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = include

SRC := $(wildcard $(SRC_PATH)/*.c)

OBJ = $(addprefix $(OBJ_PATH)/, $(notdir $(SRC:.c=.o)))

HEADERS = -I $(INC_PATH)

VIOLET = \033[38;5;129m
RESET = \033[0m
U_LINE = \033[4m
PINK = \033[1;38;5;206m

all: $(NAME)

$(NAME): $(OBJ)
	@$(ARFLAGS) $@ $(OBJ)
	@echo "\n$(VIOLET)$(U_LINE)🌸 $(NAME): Compiled 🌸 $(RESET) \n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "$(PINK)libft Compiling:$(RESET) $(notdir $<)"

clean:
	@$(REMOVE) $(OBJ_PATH)

fclean: clean
	@$(REMOVE) $(NAME)

re: fclean all

.PHONY: all clean fclean re
