# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 21:36:03 by tyasmine          #+#    #+#              #
#    Updated: 2019/04/07 21:59:39 by tyasmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFILE = *.c

OBJ = *.o

INC = ../includes

all: $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra -I $(INC) -c $(CFILE)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
