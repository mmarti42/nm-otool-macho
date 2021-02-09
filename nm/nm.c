#include "nm.h"

void *ft_mmap(char *filename, size_t *fsize)
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
	if ((mapped = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
		fatal_err(strerror(errno));
	close(fd);
	*fsize = st.st_size;
	return (mapped);
}

t_symbol *get_sym_list(t_symtab_command *sc, char *mapped)
{
	char	*strtab;
	void	*syms;

	strtab = mapped + sc->stroff;
	syms = (mapped + sc->symoff);
//	if (g_file_type == archx86)  //todo
//		return (fill_sym_list32(syms, strtab, sc->nsyms, mapped));
	return (fill_sym_list64(syms, strtab, sc->nsyms, mapped));
}

void print_sym_list(t_symbol *symlist)
{
	while (symlist)
	{
		if (symlist->addr && *(symlist->name))
			ft_printf("%016llx %c ", symlist->addr, symlist->type);
		else if (*(symlist->name))
			ft_printf("%16s %c ", " ", symlist->type);
		if (*(symlist->name))
			ft_putendl(symlist->name);
		symlist = symlist->next;
	}
}

void print_symtab(char *filename)
{
	t_mach_header		*mapped;
	size_t				fsize;
	t_symbol 			*sym_list;
	t_symtab_command 	*sc;

	if (!(mapped = (t_mach_header *)ft_mmap(filename, &fsize)))
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
			print_sym_list(sym_list);
			//todo free_sym_list(sym_list);
		}
	}
	if (munmap(mapped, fsize) < 0)
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
		while (*args)
			print_symtab(*args++);
	}
	return (0);
}