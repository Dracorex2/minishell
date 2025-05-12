NAME = minishell

CFLAGS = -Wall -Wextra -Werror -g
SRCS = src/main.c\
	src/parsing/parsing.c src/parsing/redirections.c \
	src/execution/exec.c\
	src/memory/ft_mem.c\
	src/utils/ft_split.c\
	src/utils/ft_str_utils.c src/utils/ft_str_utils2.c src/utils/ft_str_utils3.c\
	src/utils/ft_setenv.c\
	src/builtin/echo.c src/builtin/exit.c src/builtin/cd.c
	
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