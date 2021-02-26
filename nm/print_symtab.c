/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symtab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:09:39 by mmarti            #+#    #+#             */
/*   Updated: 2021/02/25 20:09:40 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_symbol			*get_sym_list(t_symtab_command *sc, char *mapped)
{
	char	*strtab;
	void	*syms;

	strtab = mapped + sc->stroff;
	syms = (mapped + sc->symoff);
	if ((long)(strtab - mapped) > g_cfsize || (long)syms +
	(long)(sc->nsyms) - (long)mapped > g_cfsize)
		fatal_err("corrupted");
	if (g_file_magic == archx86)
		return (fill_sym_list32(syms, strtab, sc->nsyms, mapped));
	return (fill_sym_list64(syms, strtab, sc->nsyms, mapped));
}

static void				print_one_symbol(t_symbol *symlist, char *fname)
{
	if ((g_opt.u && symlist->type != 'U') || (g_opt.g && symlist->type < 'A'))
		return ;
	if (g_opt.aa)
		ft_printf("%s: ", fname);
	if ((symlist->addr || symlist->type != 'U') &&
	*(symlist->name) && symlist->type != 'I')
	{
		if (g_file_magic == archx64)
			ft_printf("%016llx %c ", symlist->addr, symlist->type);
		else
			ft_printf("%08llx %c ", symlist->addr, symlist->type);
	}
	else
	{
		if (g_file_magic == archx64)
			ft_printf("%16s %c ", " ", symlist->type);
		else
			ft_printf("%8s %c ", " ", symlist->type);
	}
	if (*(symlist->name))
		ft_putstr(symlist->name);
	if (symlist->type == 'I')
		ft_printf(" (indirect for %s)", symlist->name);
	ft_putchar('\n');
}

static void				print_sym_list(t_symbol *symlist, char *fname)
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
	else
	{
		while (symlist)
		{
			print_one_symbol(symlist, fname);
			symlist = symlist->next;
		}
	}
}

static t_mach_header	*get_mapped(char *filename)
{
	t_mach_header	*mapped;

	if (!(mapped = (t_mach_header *)ft_mmap(filename)))
		return (NULL);
	if (*(uint32_t *)mapped == FAT_CIGAM)
	{
		mapped = handle_fat(mapped);
		g_file_type = fat;
	}
	else
		g_file_type = mapped->filetype;
	if (mapped->magic != MH_MAGIC && mapped->magic != MH_MAGIC_64)
	{
		ft_putstr_fd("The file was not recognized"\
		"as a valid object file\n", STDERR_FILENO);
		return (NULL);
	}
	return ((t_mach_header *)mapped);
}

void					print_symtab(char *filename)
{
	t_mach_header		*mapped;
	t_symbol			*sym_list;
	t_symtab_command	*sc;
	t_mach_header		*mapped_tmp;

	if (!(mapped = get_mapped(filename)))
		return ;
	mapped_tmp = mapped;
	g_file_magic = mapped->magic;
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
	if (munmap((void *)mapped_tmp, g_cfsize) < 0)
		return (fatal_err(strerror(errno)));
}
