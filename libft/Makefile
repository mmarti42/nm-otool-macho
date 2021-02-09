# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tyasmine <kbessa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/01 14:51:29 by kbessa            #+#    #+#              #
#    Updated: 2019/10/08 14:17:48 by kbessa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=		libftprintf.a
CC		    = 		gcc
CFLAGS 		= 		-g -I includes/ -Wall -Wextra -Werror -O1
OBJ 		= 		$(SRC:.c=.o)

C_OK		=		"\033[35m"
C_GOOD		=		"\033[32m"
C_NO		=		"\033[00m"

SUCCESS		=		$(C_GOOD)SUCCESS$(C_NO)
OK			=		$(C_OK)OK$(C_NO)

SRC         =	srcs/ft_printf.c srcs/f_frac.c srcs/f_get_ent.c srcs/f_lst.c srcs/f_parse.c srcs/f_putnum.c \
                srcs/f_round.c srcs/f_spec.c srcs/f_sup.c srcs/f_sup2.c srcs/float.c srcs/ft_lib_f.c srcs/ft_output.c \
                srcs/ft_output_csp.c srcs/ft_output_d.c srcs/ft_output_x.c srcs/ft_pars.c srcs/ft_prt.c

all: $(NAME)

%.o: %.c
	@printf "[ft_printf] Compiling [.:]\r"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "[ft_printf] Compiling [:.]\r"

$(NAME): $(OBJ)
	@make -C libft/

	@cp libft/libft.a ./$(NAME)
	@ar rc $@ $^
	@ranlib $@
	@echo "Compiling & indexing" [ $(NAME) ] $(SUCCESS)

clean:
	@make clean -C libft/
	@/bin/rm -f $(OBJ)
	@printf "[ft_printf] Removed object files!\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)

re: fclean all

ifeq ($(shell uname),Darwin)
test: re
	cd tests/tests && $(MAKE) test
else
test: re
	@echo "\n\n\033[45mBuild ok, launch tests on OSX\033[0m\n\n"
	exit 0
endif

.PHONY: all clean fclean re test
