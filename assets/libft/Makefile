NAME = libft.a

CC = cc
CFLAGS =  -Wall -Wextra -Werror
ARFLAGS = ar -rcs
REMOVE = rm -rf

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = include

SRC_FILES = ft_atof.c ft_atoi.c ft_bzero.c \
ft_calloc.c ft_isalnum.c ft_isascii.c \
ft_isalpha.c ft_isdigit.c ft_isprint.c \
ft_isspace.c ft_isspecialchar.c ft_itoa.c \
ft_itoalong.c ft_lstadd_back.c ft_lstadd_front.c \
ft_lstlast.c ft_lstnew.c ft_memchr.c \
ft_memcmp.c ft_memcpy.c ft_memmove.c \
ft_memset.c ft_split.c ft_strchr.c \
ft_strdup.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlcpy.c ft_strlen.c \
ft_strmapi.c ft_strncmp.c ft_strndup.c \
ft_strnstr.c ft_strrchr.c ft_strtrim.c \
ft_substr.c ft_tolower.c ft_toupper.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_putstr.c ft_putchar.c \
ft_putdec.c ft_putdeclong.c ft_putvoid.c \
ft_puthexa.c \

SRC := $(addprefix $(SRC_PATH)/, $(SRC_FILES))

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
