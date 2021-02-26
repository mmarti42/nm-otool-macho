/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 21:11:50 by mmarti            #+#    #+#             */
/*   Updated: 2021/02/25 21:11:52 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void		print_other(size_t size, const unsigned char *text, long mapped, long offs)
{
	if (size)
	{
		ft_printf("%016llx ", text - mapped + offs);
		while (size)
		{
			ft_printf("%02x ", *text);
			size--;
			text++;
		}
		ft_putchar('\n');
	}
}

long		get_offset(long offs, t_mach_header *mapped)
{
	if (mapped->filetype == shared)
		return (0);
	if (g_file_type == fat || g_file_type == executable)
		return (0x100000000);
	else if (g_file_type == relocatable)
		return (-offs);
	else
		return (0);
}

void		print_text(t_text *t, char *fname, long mapped)
{
	long				offs;
	const unsigned char	*text;
	size_t				size;

	size = t->size;
	text = t->text;
	offs = get_offset((long)text - (long)mapped, (t_mach_header *)mapped);
	if (!size)
		return ;
	ft_printf("%s:\n%s\n", fname, "Contents of (__TEXT,__text) section");
	while (size > 16)
	{
		ft_printf("%016lx ", (long)text - mapped + offs);
		ft_printf("%02x %02x %02x %02x %02x %02x %02x %02x %02x ",
		text[0], text[1], text[2], text[3],\
		text[4], text[5], text[6], text[7], text[8]);
		ft_printf("%02x %02x %02x %02x %02x %02x %02x \n", 
		text[9], text[10],\
		text[11], text[12], text[13], text[14], text[15]);
		text += 16;
		size -= 16;
	}
	print_other(size, text, mapped, offs);
}

static void	print_text_sect(char *fname)
{
	t_mach_header	*mapped;
	t_text			text;
	t_mach_header	*mapped_tmp;

	ft_bzero(&text, sizeof(t_text));
	if (!(mapped = (t_mach_header *)ft_mmap(fname)))
		return ;
	mapped_tmp = mapped;
	if (*(uint32_t *)mapped == FAT_CIGAM)
	{
		mapped = handle_fat(mapped);
		g_file_type = fat;
	}
	else
		g_file_type = mapped->filetype;
	if (mapped->magic != MH_MAGIC && mapped->magic != MH_MAGIC_64)
		ft_putstr_fd("The file was not recognized"
		"as a valid object file\n", STDERR_FILENO);
	else
	{
		g_file_magic = mapped->magic;
		if (get_text(&text, mapped) < 0)
			ft_putstr_fd("Can't find text sect\n", STDERR_FILENO);
		print_text(&text, fname, (long)mapped);
	}
	if (munmap((void *)mapped_tmp, g_cfsize) < 0)
		return (fatal_err(strerror(errno)));
}

int			main(int ac, char **av)
{
	(void)ac;
	if (ac < 2)
		ft_printf("usage: %s\n", USAGE);
	else
	{
		if (G_CPU < 0)
			ft_printf("\\u001b[34mWarning\\u001b[34m: unknown host cpu type\n");
		while (*++av)
			print_text_sect(*av);
	}
	return (0);
}
