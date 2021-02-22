ROOT := ..

include $(ROOT)/Makefile.global

NAME := $(ROOT)/ft_otool

SOURCES := otool.c

OBJ_DIR := objs

INCLUDES := ft_macho.h\
	otool.h

OBJS := $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

INC := $(LIB_INC) $(addprefix $(INCLUDES_DIR)/,$(INCLUDES))

.PHONY: compile clean fclean re

compile: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(UTL_O)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(UTL_O) $(LIBFT)

$(filter $(OBJ_DIR)/%.o,$(OBJS)): $(OBJ_DIR)/%.o: %.c $(INC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -I $(INCLUDES_DIR) -I $(LIBFT_INCLUDES_DIR) -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT): $(LIBFT_INC)
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(UTILS_OBJ_DIR)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean compile
