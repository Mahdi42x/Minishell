
NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g

LIBS	=	 ./libft/libft.a

SRCS	=	minishell.c\
			src/bash.c\
			src/free.c\
			execution/read1.c

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
