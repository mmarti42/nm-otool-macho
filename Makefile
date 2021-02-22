NM := ft_nm

OTOOL := ft_otool

NM_DIR := nm

OTOOL_DIR := otool

.PHONY: $(OTOOL) $(NM)

all: $(NM) $(OTOOL)

$(NM):
	make -C $(NM_DIR)

$(OTOOL):
	make -C $(OTOOL_DIR)

clean:
	make clean -C $(NM_DIR)
	make clean -C $(OTOOL_DIR)

fclean:
	make fclean -C $(NM_DIR)
	make fclean -C $(OTOOL_DIR)

re: fclean all