
NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g
LDFLAGS = -lreadline

LIBS	=	 ./libft/libft.a

HEADER = minishell.h

MAIN = minishell signal

PARSING = line tokens

TOOLS = free parsing type

SRCS =	$(addsuffix .c, $(addprefix srcs/main/, $(MAIN))) \
		$(addsuffix .c, $(addprefix srcs/parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix srcs/tools/, $(TOOLS))) \
		# $(addsuffix .c, $(addprefix srcs/builtins/, $(BUILTINS))) \
		# $(addsuffix .c, $(addprefix srcs/env/, $(ENV))) \
		# $(addsuffix .c, $(addprefix srcs/exec/, $(EXEC))) \


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

norm:
	norminette $(SRCS) includes/$(HEADER)

.PHONY: all clean fclean re norm
