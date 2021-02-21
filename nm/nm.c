#include "nm.h"

char **ft_nm_getopt(const char **av)
{
	char 	buf[6];
	int		i;
	char	**ret;

	i = -1;
	if (!(ret = parse_opt(av, "pruAg", buf)))
		fatal_err(USAGE);
	while (buf[++i])
	{
		if (buf[i] == 'p')
			g_opt.p = true;
		else if (buf[i] == 'u')
			g_opt.u = true;
		else if (buf[i] == 'g')
			g_opt.g = true;
		else if (buf[i] == 'r')
			g_opt.r = true;
		else if (buf[i] == 'A')
			g_opt.aa = true;
	}
	if (ret[1])
		g_opt.print_files = true;
	return (ret);
}

t_symbol *get_sym_list(t_symtab_command *sc, char *mapped)
{
	char	*strtab;
	void	*syms;

	strtab = mapped + sc->stroff;
	syms = (mapped + sc->symoff);
	if ((off_t)(strtab - mapped) > g_cfsize  || (char *)syms + sc->nsyms - mapped > (long long)g_cfsize)
		fatal_err("corrupted");
	if (g_file_type == archx86)
		return (fill_sym_list32(syms, strtab, sc->nsyms, mapped));
	return (fill_sym_list64(syms, strtab, sc->nsyms, mapped));
}

void print_one_symbol(t_symbol *symlist, char *fname)
{
	if ((g_opt.u && symlist->type != 'U') || (g_opt.g && symlist->type < 'A'))
		return;
	if (g_opt.aa)
		ft_printf("%s: ", fname);
	if (symlist->addr && *(symlist->name))
	{
		if (g_file_type == archx64)
			ft_printf("%016llx %c ", symlist->addr, symlist->type);
		else
			ft_printf("%08llx %c ", symlist->addr, symlist->type);
	}
	else if (*(symlist->name))
	{
		if (g_file_type == archx64)
			ft_printf("%16s %c ", " ", symlist->type);
		else
			ft_printf("%8s %c ", " ", symlist->type);
	}
	if (*(symlist->name))
		ft_putendl(symlist->name);
}

void print_sym_list(t_symbol *symlist, char *fname)
{
	if (g_opt.r)
	{
		while (symlist->next)
			symlist = symlist->next;
		while (symlist)
		{
			print_one_symbol(symlist, fname);
			symlist = symlist->prev;
		}
	}
	else {
		while (symlist) {
			print_one_symbol(symlist, fname);
			symlist = symlist->next;
		}
	}
}

uint32_t	b_swap32(uint32_t x)
{
#ifdef __LITTLE_ENDIAN__
	return ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8)
			| (((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24));
#endif
	return (x);
}

t_mach_header *handle_fat(void *mapped)
{
	uint64_t num;
	struct fat_arch *it;
	t_mach_header *ret;

	ret = NULL;
	if ((num = b_swap32(((struct fat_header *)mapped)->nfat_arch)) * sizeof(struct fat_header) + 1 > (uint64_t)g_cfsize)
		fatal_err("corrupted");
	it = (struct fat_arch *)((char *)mapped + sizeof(struct fat_header));
	if (G_CPU == -1)
		return (t_mach_header *)((char *)mapped + it->offset);
	while (num--)
	{
		if (b_swap32(it->cputype) == G_CPU)
			ret =  (t_mach_header *)((char *)mapped + b_swap32(it->offset));
		it++;
	}
	if (!ret)
		return (t_mach_header *)((char *)mapped +
		b_swap32((((struct fat_arch *)((char *)mapped + sizeof(struct fat_header)))->offset)));
	g_cfsize -= (char *)ret - (char *)mapped;
	return ret;
}

void free_sym_list(t_symbol *symlist)
{
	t_symbol *tmp;

	while (symlist)
	{
		tmp = symlist;
		symlist = symlist->next;
		free(tmp);
	}
}

void print_symtab(char *filename)
{
	t_mach_header		*mapped;
	t_symbol 			*sym_list;
	t_symtab_command 	*sc;

	if (!(mapped = (t_mach_header *)ft_mmap(filename)))
		return ;
	if (*(uint32_t *)mapped == FAT_CIGAM)
		mapped = handle_fat(mapped);
	if (mapped->magic != MH_MAGIC && mapped->magic != MH_MAGIC_64)
		ft_putstr_fd("The file was not recognized as a valid object file\n", STDERR_FILENO);
	else {
		g_file_type = mapped->magic;
		if (!(sc = get_lc(LC_SYMTAB, mapped)))
			ft_putstr_fd("Symbols not found\n", STDERR_FILENO);
		else
		{
			sym_list = get_sym_list(sc, (char *)mapped);
			if (g_opt.print_files == true)
				ft_printf("%s:\n", filename);
			print_sym_list(sym_list, filename);
			free_sym_list(sym_list);
		}
	}
	if (munmap(mapped, g_cfsize) < 0)
		return (fatal_err(strerror(errno)));
}

int main(int ac, char **av)
{
	char **args;

	(void)ac;
	if (G_CPU < 0)
		ft_printf("\\u001b[34mWarning\\u001b[34m: unknown host cpu type\n");
	args = ft_nm_getopt((const char **)av);
	if (!*args)
		 print_symtab("a.out");
	else
	{
		while (*args) {
			if (args[1])
				ft_putchar('\n');
			print_symtab(*args++);
		}
	}
	return (0);
}
