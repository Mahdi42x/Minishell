
NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g
LDFLAGS = -lreadline

LIBS	=	 ./libft/libft.a

SRCS	=	minishell.c\
			src/bash.c\
			src/free.c\
			src/signal.c\
			execution/execute.c\
			execution/cd_exec.c\
			execution/exit_exec.c\
			execution/pwd_exec.c\
			execution/echo_exec.c\
			execution/ls_exec.c\
			execution/env_exec.c\
			parsing/echo_parsing.c

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME): $(OBJS)
			make -C  ./libft
			$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) $(LDFLAGS)

clean:
			make clean -C  ./libft
			rm -rf $(OBJS)
			
fclean:		clean
			rm -rf $(NAME) $(LIBS)

re:			fclean all

.PHONY: all clean fclean re
