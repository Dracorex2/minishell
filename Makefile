NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g -Iincludes
SRCS = src/main.c\
	src/parsing/parsing.c src/parsing/redirections.c src/parsing/heredoc.c \
	src/execution/exec.c\
	src/execution/command.c\
	src/execution/exec_single.c\
	src/execution/redirection.c\
	src/memory/ft_mem.c\
	src/utils/ft_split.c\
	src/utils/len_utils.c\
	src/utils/memory.c\
	src/utils/ft_str_utils.c src/utils/ft_str_utils2.c src/utils/ft_str_utils3.c\
	src/utils/env/cpy_env.c\
	src/utils/env/env_utils.c\
	src/utils/env/rm_var_env.c\
	src/utils/env/set_var_env.c\
	src/builtin/echo.c src/builtin/exit.c src/builtin/cd.c src/builtin/unset.c src/builtin/export.c src/builtin/env.c src/builtin/pwd.c
	
OBJS = $(SRCS:.c=.o)
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

dev: fclean
	git add *; git commit -m "dev"; git push;

.PHONY: all clean fclean re dev