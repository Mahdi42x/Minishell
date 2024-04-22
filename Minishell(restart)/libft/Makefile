# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mawada <mawada@student.42berlin.de>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 15:22:24 by mawada            #+#    #+#              #
#    Updated: 2024/04/22 14:10:59 by mawada           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strcmp.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c ft_memdel.c ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c \
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c ft_striteri.c ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c \
					ft_printf.c print_command.c print_command_2.c get_next_line.c get_next_line_utils.c\
					ft_skip/ft_skip_char.c ft_skip/ft_skip_chars.c ft_skip/ft_skip_space.c\
					ft_skip/ft_skip_spacenl.c ft_isin.c

B_SRC			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c
					
OBJS			= $(SRCS:.c=.o)

B_OBJS			= $(B_SRC:.c=.o)

HEADER			= libft.h

CC			= cc
RM			= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= libft.a

all:			$(NAME) $(bonus)

$(NAME): $(OBJS)
	@echo "\n\n\033[0;32mCompiling libft..."
	@ar rc $(NAME) $^
	@ranlib $(NAME)
	@echo "\033[0m"

%.o: %.c
	@printf "\033[0;33mGenerating libft objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@
			
bonus:			$(B_OBJS)
			ar rc $(NAME) $(B_OBJS)
			ranlib $(NAME)

clean:
			$(RM) $(OBJS) $(B_OBJS)

fclean:			clean
			$(RM) $(NAME) $(bonus)

re:			fclean $(NAME)

norm:
	norminette $(SRCS) $(HEADER)

.PHONY:			all clean fclean re norm
