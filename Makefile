NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes #-fsanitize=address
SRCS = src/main.c\
	src/parsing/parsing.c src/parsing/redirections.c src/parsing/heredoc.c src/parsing/env_variables.c src/parsing/quotes.c src/parsing/check_line.c \
	src/execution/exec.c\
	src/execution/command.c\
	src/execution/exec_single_utils.c\
	src/execution/exec_multiple_utils.c\
	src/execution/exec_multiple_pipes.c\
	src/execution/redirection.c\
	src/execution/builtins.c\
	src/memory/ft_mem.c\
	src/utils/atoi_error.c\
	src/utils/ft_split.c\
	src/utils/len_utils.c\
	src/utils/memory.c\
	src/utils/ft_str_utils.c src/utils/ft_str_utils2.c src/utils/ft_str_utils3.c src/utils/ft_str_utils4.c src/utils/ft_str_utils5.c\
	src/utils/env/cpy_env.c\
	src/utils/env/env_utils.c\
	src/utils/env/rm_var_env.c\
	src/utils/env/set_var_env.c\
	src/utils/itoa.c\
	src/builtin/echo.c src/builtin/exit.c src/builtin/cd.c src/builtin/unset.c src/builtin/export.c src/builtin/env.c src/builtin/pwd.c
	
OBJS = $(SRCS:.c=.o)
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: $(NAME)
	@echo "Running Valgrind on $(NAME)"
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --suppressions=readline.sup ./$(NAME)

dev: fclean
	git add *; git commit -m "dev"; git push --force

.PHONY: all clean fclean re dev debug