#include "nm.h"

char get_sym_type(uint8_t n_type)
{
	char ret;
	uint8_t type_bits;

	type_bits = n_type & N_TYPE;
	if (!type_bits)
		return 'U';
	else if (type_bits & N_ABS)
		ret = 'A';
	else if (type_bits & N_INDR)
		ret = 'I';
	else
		return '?';
	return ret;
}

static char get_sym_sect64(char *mapped, uint8_t n_sect)
{
	struct segment_command_64 *segment;
	struct section_64 *section;

	segment = (struct segment_command_64 *)get_lc(LC_SEGMENT_64, (t_mach_header *) mapped);
	while (1)
	{
		if (segment->nsects >= n_sect)
			break ;
		n_sect -= segment->nsects;
		segment = (struct segment_command_64 *)next_com((t_load_command *)segment);
	}
	if (!ft_strcmp(segment->segname, "__TEXT"))
		return 'T';
	section = (struct section_64 *)(((char *)segment) + sizeof(struct segment_command_64));
	while (--n_sect)
		section++;
	if (!ft_strcmp(section->segname, "__DATA"))
	{
		if (!ft_strcmp(section->sectname, "__data"))
			return 'D';
		if (!ft_strcmp(section->sectname, "__bss"))
			return 'B';
	}
	return 'S';
}

t_symbol *fill_sym_list64(t_nlist_64 *syms, char *strtab, size_t i, char *mapped)
{
	t_symbol *sym_list;
	t_symbol *new;

	sym_list = NULL;
	while (i--)
	{
		if (!(syms->n_type & N_STAB))
		{
			new = (t_symbol *) xmalloc(sizeof(t_symbol));
			new->name = strtab + syms->n_un.n_strx;
			new->addr = syms->n_value;
			if (syms->n_sect == NO_SECT)
				new->type = get_sym_type(syms->n_type);
			else
				new->type = get_sym_sect64(mapped, syms->n_sect);
			if (!(syms->n_type & N_EXT))
				new->type += 32;
			sym_list = insert_sym(new, sym_list);
		}
		syms++;
	}
	return sym_list;
}
