NAME = minishell

CC = gcc -g -o $(NAME)
CFLAGS = -Wall -Wextra -Werror -g3
LREADLINE = -L/Users/$(USER)/.brew/opt/readline/lib  -lreadline
REMOVE = rm -rf

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = include
FREE_PATH = free
BUILT-INS_PATH = built-ins
PARSER_PATH = parser
PIPEX_PATH = pipex
SIGNALS_PATH = signals
LIBFT_PATH = assets/libft
HEADERS	= -I ./include  -I /System/Volumes/Data/Users/$(USER)/.brew/Cellar/readline/8.2.1/include/
LIBS = $(LIBFT_PATH)/libft.a

SRC = $(SRC_PATH)/$(FREE_PATH)/free_all.c \
	\
	$(SRC_PATH)/$(BUILT-INS_PATH)/cd_utils.c $(SRC_PATH)/$(BUILT-INS_PATH)/cd.c $(SRC_PATH)/$(BUILT-INS_PATH)/echo.c $(SRC_PATH)/$(BUILT-INS_PATH)/env_array_utils.c \
	$(SRC_PATH)/$(BUILT-INS_PATH)/env.c $(SRC_PATH)/$(BUILT-INS_PATH)/exit.c $(SRC_PATH)/$(BUILT-INS_PATH)/export_utils.c $(SRC_PATH)/$(BUILT-INS_PATH)/export_utils2.c \
	$(SRC_PATH)/$(BUILT-INS_PATH)/export.c $(SRC_PATH)/$(BUILT-INS_PATH)/pwd.c $(SRC_PATH)/$(BUILT-INS_PATH)/refill_envp_lst.c $(SRC_PATH)/$(BUILT-INS_PATH)/tuple_utils.c \
	$(SRC_PATH)/$(BUILT-INS_PATH)/tuple_utils2.c $(SRC_PATH)/$(BUILT-INS_PATH)/unset.c \
	\
	$(SRC_PATH)/$(PARSER_PATH)/expan_core.c $(SRC_PATH)/$(PARSER_PATH)/expan_utils.c $(SRC_PATH)/$(PARSER_PATH)/group_core.c \
	$(SRC_PATH)/$(PARSER_PATH)/group_cmd_lst.c $(SRC_PATH)/$(PARSER_PATH)/group_here_doc.c $(SRC_PATH)/$(PARSER_PATH)/group_redir.c \
	$(SRC_PATH)/$(PARSER_PATH)/group_utils.c $(SRC_PATH)/$(PARSER_PATH)/token_core.c $(SRC_PATH)/$(PARSER_PATH)/token_delete_token_sep.c \
	$(SRC_PATH)/$(PARSER_PATH)/token_concat_token_word.c $(SRC_PATH)/$(PARSER_PATH)/token_handlers.c \
	\
	$(SRC_PATH)/$(PIPEX_PATH)/pipex_utils.c $(SRC_PATH)/$(PIPEX_PATH)/pipex_utils2.c $(SRC_PATH)/$(PIPEX_PATH)/pipex.c \
	\
	$(SRC_PATH)/$(SIGNALS_PATH)/signals.c \
	\
	$(SRC_PATH)/init.c $(SRC_PATH)/init_utils.c \

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
