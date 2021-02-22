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
	t_mach_header		*mapped_tmp;

	if (!(mapped = (t_mach_header *)ft_mmap(filename)))
		return ;
	mapped_tmp = mapped;
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
	if (munmap(mapped_tmp, g_cfsize) < 0)
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
