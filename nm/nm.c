#include "nm.h"

void *ft_mmap(char *filename)
{
	int fd;
	char *mapped;
	struct stat st;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar('\n');
		close(fd);
		return NULL;
	}
	if (fstat(fd, &st) < 0)
		fatal_err(strerror(errno));
	if ((g_cfsize = st.st_size) <= (off_t)0x1000)
	{
		ft_putstr_fd("not binary\n", STDERR_FILENO);
		return NULL;
	}
	if ((mapped = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
		fatal_err(strerror(errno));
	close(fd);
	return (mapped);
}

t_symbol *get_sym_list(t_symtab_command *sc, char *mapped)
{
	char	*strtab;
	void	*syms;

	strtab = mapped + sc->stroff;
	syms = (mapped + sc->symoff);
	if ((off_t)(strtab - mapped) > g_cfsize  || (char *)syms + sc->nsyms - mapped > (long long)g_cfsize)
		fatal_err("corrupted");
//	if (g_file_type == archx86)  //todo
	return (fill_sym_list64(syms, strtab, sc->nsyms, mapped));
}

void print_one_symbol(t_symbol *symlist, char *fname)
{
	if ((g_opt.u && symlist->type != 'U') || (g_opt.g && symlist->type < 'A'))
		return;
	if (g_opt.aa)
		ft_printf("%s: ", fname);
	if (symlist->addr && *(symlist->name))
		ft_printf("%016llx %c ", symlist->addr, symlist->type);
	else if (*(symlist->name))
		ft_printf("%16s %c ", " ", symlist->type);
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

void print_symtab(char *filename)
{
	t_mach_header		*mapped;
	t_symbol 			*sym_list;
	t_symtab_command 	*sc;

	if (!(mapped = (t_mach_header *)ft_mmap(filename)))
		return ;
	if (mapped->magic != MH_MAGIC && mapped->magic != MH_MAGIC_64)
		ft_putstr_fd("The file was not recognized as a valid object file", STDERR_FILENO);
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
			//todo free_sym_list(sym_list);
		}
	}
	if (munmap(mapped, g_cfsize) < 0)
		return (fatal_err(strerror(errno)));
}

int main(int ac, char **av)
{
	char **args;

	(void)ac;
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
