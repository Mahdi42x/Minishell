
NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g

LIBS	=	 ./libft/libft.a

SRCS	=	minishell.c\
			src/bash.c\
			src/free.c\
			execution/execute.c\
			execution/exit_exec.c\
			execution/pwd_exec.c\
			execution/echo_exec.c\
			parsing/echo_parsing.c\

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME): $(OBJS)
			make -C  ./libft
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
			make clean -C  ./libft
			rm -rf $(OBJS)
			
fclean:		clean
			rm -rf $(NAME) $(LIBS)

re:			fclean all

.PHONY: all clean fclean re
