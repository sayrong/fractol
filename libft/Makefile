# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: balvyn-s <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/03 20:03:27 by balvyn-s          #+#    #+#              #
#    Updated: 2018/12/15 15:44:11 by balvyn-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAG = -Wextra -Wall -Werror -I.
GCC = gcc $(FLAG)

all: $(NAME)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

$(NAME):
	$(GCC) -c *.c
	ar rc $(NAME) *.o
