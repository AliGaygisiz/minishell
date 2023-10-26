SRCS = ./src/main.c \
		./src/utils_files/utils.c \
		./src/utils_files/libft_strjoin.c \
		./src/utils_files/reset_utils.c \
		./src/utils_files/libft_split.c \
		./src/utils_files/libft_atoi.c \
		./src/utils_files/libft_itoa.c \
		./src/utils_files/libft_calloc.c \
		./src/signal/signal.c \
		./src/parser/parser.c \
		./src/parser/parser_utils.c \
		./src/parser/parser_utils_2.c \
		./src/syntax_control.c \
		./src/readline.c \
		./src/redirection/heredoc.c \
		./src/redirection/input.c \
		./src/redirection/append.c \
		./src/redirection/output.c \
		./src/redirection/duplicate.c \
		./src/redirection/general.c \
		./src/redirection/redirection_utils.c \
		./src/redirection/redirection_utils_2.c \
		./src/execute/delete_quote.c \
		./src/execute/abs_path.c \
		./src/execute/general_utils.c \
		./src/execute/multi_command_execute.c \
		./src/execute/one_command_execute.c \
		./src/execute/nav_execute.c \
		./src/builtins/cd.c \
		./src/builtins/echo.c \
		./src/builtins/env_utils.c \
		./src/builtins/exit.c \
		./src/builtins/export.c \
		./src/builtins/pwd.c \
		./src/builtins/env.c \
		./src/builtins/unset.c \
		./src/builtins/nav_builtins.c \
		./src/builtins/export_utils.c \
		./src/builtins/variables.c
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES	= -I. -I ./lib/lib/readline/include
RM = rm -rf
READLINE			=	-lreadline
LIB				= ./lib/.minishell
LINKERS		=  $(READLINE) -L ./lib/lib/readline/lib

all: $(LIB) ${NAME}


$(NAME): $(SRCS) $(LIB)
	@gcc $(CFLAGS) $(LDFLAGS) $(SRCS) $(INCLUDES) $(LINKERS) -o $(NAME)

$(LIB):
	@make -C ./lib

fclean:
	@${RM} $(NAME)

fffclean: fclean
	@make fclean -C ./lib

re: fclean all

.PHONY: all bonus fclean re
