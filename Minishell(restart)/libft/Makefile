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

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes/

HEADER = $(addsuffix .h, $(addprefix includes/, libutils get_next_line ft_printf))

FTIS = alnum alpha ascii count digit in print space spacenl where

FTSKIP = space spacenl char chars

FTLST = add_back add_front clear delone iter last map new size

FTMATH = abs nbrlen hexlen baselen power

FTMEM = bzero calloc memccpy memchr memcmp memcpy memdel memmove memset

FTPUT = char endl nbr str char_fd endl_fd nbr_fd str_fd

FTSTR = chr cmp dup isnum join lcat lcpy len mapi ncmp nstr rchr trim

FTSUB = ft_str/ft_substr ft_str/ft_split

FTTO = tolower toupper atoi itoa

FTEX = gnl/get_next_line printf/ft_printf

FTPRF = command command_2

FTGNL = utils

SRC = $(addsuffix .c, $(addprefix ft_is/ft_is, $(FTIS))) \
	$(addsuffix .c, $(addprefix ft_lst/ft_lst, $(FTLST))) \
	$(addsuffix .c, $(addprefix ft_math/ft_, $(FTMATH))) \
	$(addsuffix .c, $(addprefix ft_mem/ft_, $(FTMEM))) \
	$(addsuffix .c, $(addprefix ft_put/ft_put, $(FTPUT))) \
	$(addsuffix .c, $(addprefix ft_skip/ft_skip_, $(FTSKIP))) \
	$(addsuffix .c, $(addprefix ft_str/ft_str, $(FTSTR)) $(FTSUB)) \
	$(addsuffix .c, $(addprefix ft_to/ft_, $(FTTO))) \
	$(addsuffix .c, $(addprefix ft_, $(FTEX))) \
	$(addsuffix .c, $(addprefix ft_printf/print_, $(FTPRF))) \
	$(addsuffix .c, $(addprefix ft_gnl/get_next_line_, $(FTGNL))) \

OBJ = $(SRC:.c=.o)

all: $(NAME)


$(NAME): $(OBJ)
	@echo "\n\n\033[0;32mCompiling libft..."
	@ar rc $(NAME) $^
	@ranlib $(NAME)
	@echo "\033[0m"

%.o: %.c
	@printf "\033[0;33mGenerating libft objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRC) $(HEADER)

.PHONY: all clean fclean re norm
