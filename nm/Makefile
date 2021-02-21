ROOT := ..

#can be added to Makefile.global later

CC := clang

CFLAGS := -g -Wall -Wextra -Werror


UTILS := utils.c

UTILS_OBJ := utils.o

UTILS_DIR := $(ROOT)/utils

UTL_O := $(addprefix $(UTILS_DIR)/,$(UTILS_OBJ))

UTL := $(addprefix $(UTILS_DIR)/,$(UTILS))


INCLUDES_DIR := $(ROOT)/includes


LIBFT_DIR := $(ROOT)/libft

LIBFT_INCLUDES := libft.h\
	ft_printf.h

LIBFT_INCLUDES_DIR := $(LIBFT_DIR)/includes


LIBFT := $(LIBFT_DIR)/libftprintf.a

LIB_INC := $(wildcard $(LIBFT_INCLUDES_DIR)/$(LIBFT_INCLUDES))


#-------------------------

.PHONY: all clean fclean re

NAME := ft_nm

SOURCES := nm.c\
	fill_sym_list.c\
	get_lc.c\
	insert_sym.c

OBJ_DIR := objs

OBJS := $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

INCLUDES := ft_macho.h\
	nm.h

INC := $(LIB_INC) $(addprefix $(INCLUDES_DIR)/,$(INCLUDES))

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(UTL_O) $(LIBFT)
	$(CC) $(CFLAGS) -o $(ROOT)/$(NAME) $(OBJS) $(UTL_O) $(LIBFT)

$(filter $(OBJ_DIR)/%.o,$(OBJS)): $(OBJ_DIR)/%.o: %.c $(INC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -I $(INCLUDES_DIR) -I $(LIBFT_INCLUDES_DIR) -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

#can be added to Makefile.global too

$(filter $(UTILS_DIR)/%.o,$(UTILS_DIR)/$(UTILS_OBJ)): $(UTILS_DIR)/%.o: $(UTL) $(INC) | $(UTL_DIR)
	$(CC) $(CFLAGS) -c -I $(INCLUDES_DIR) -I $(LIBFT_INCLUDES_DIR) -o $@ $<

$(UTL_DIR):
	mkdir -p $(UTL_DIR)

#--------------------------------

$(LIBFT): $(LIBFT_INC)
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(UTL_O)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(ROOT)/$(NAME)

re: fclean all
	make re -C $(LIBFT_DIR)