NAME = minishell

CC = gcc -g -o $(NAME)
CFLAGS = -Wall -Wextra -Werror -g0
LREADLINE = -L/Users/$(USER)/.brew/opt/readline/lib  -lreadline
REMOVE = rm -rf

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = include
LIBFT_PATH = assets/libft
HEADERS	= -I ./include  -I /System/Volumes/Data/Users/$(USER)/.brew/Cellar/readline/8.2.1/include/
LIBS = $(LIBFT_PATH)/libft.a

SRC = $(shell find $(SRC_PATH) -name '*.c')
OBJ = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRC))

ORANGE = \033[1;38;5;208m
RESET = \033[0m
U_LINE = \033[4m
YELLOW = \033[1;38;5;226m

all: $(LIBS) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBS) $(HEADERS) $(LREADLINE) -o $@
	@echo "\n$(ORANGE)$(U_LINE)⭐️ $(NAME): Compiled ⭐️$(RESET) \n"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	@echo "$(YELLOW)$(NAME) Compiling:$(RESET) $(notdir $<)"

$(LIBS):
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(REMOVE) $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@$(REMOVE) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all


.PHONY: all clean fclean re $(LIBS)
