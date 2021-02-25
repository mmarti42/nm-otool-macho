/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 21:14:42 by mmarti            #+#    #+#             */
/*   Updated: 2021/02/25 21:14:44 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int	get_text_sect64(struct segment_command_64 *seg,
t_text *buf, void *mapped)
{
	uint32_t		i;
	struct section_64	*sect;

	i = 0;
	sect = (struct section_64 *)((char *)seg + sizeof(struct segment_command_64));
	while (i++ < seg->nsects)
	{
		if ((long)sect - (long)mapped > g_cfsize)
			fatal_err("corrupted");
		if (!ft_strcmp(sect->sectname, "__text"))
		{
			buf->text = (char *)mapped + sect->offset;
			buf->size = sect->size;
			return (0);
		}
		sect++;
	}
	return (-1);
}

static int	get_text64(t_text *buf, t_mach_header *mapped)
{
	struct segment_command_64	*seg;

	seg = (struct segment_command_64 *)get_lc(LC_SEGMENT_64, mapped);
	while (1)
	{
		if (!seg)
			return (-1);
		if (!ft_strcmp(seg->segname, "__TEXT"))
			break ;
		seg = (struct segment_command_64 *)next_com((t_load_command *)seg);
		if ((long)seg - (long)mapped > g_cfsize)
			fatal_err("corrupted");
	}
	return (get_text_sect64(seg, buf, (void *)mapped));
}

static int	get_text_sect32(struct segment_command *seg,
t_text *buf, void *mapped)
{
	uint32_t		i;
	struct section	*sect;

	i = 0;
	sect = (struct section *)((char *)seg + sizeof(struct segment_command));
	while (i++ < seg->nsects)
	{
		if ((long)sect - (long)mapped > g_cfsize)
			fatal_err("corrupted");
		if (!ft_strcmp(sect->sectname, "__text"))
		{
			buf->text = (char *)mapped + sect->offset;
			buf->size = sect->size;
			return (0);
		}
		sect++;
	}
	return (-1);
}

static int	get_text32(t_text *buf, t_mach_header *mapped)
{
	struct segment_command *seg;

	seg = (struct segment_command *)get_lc(LC_SEGMENT, mapped);
	while (1)
	{
		if (!seg)
			return (-1);
		if (!ft_strcmp(seg->segname, "__TEXT"))
			break ;
		seg = (struct segment_command *)next_com((t_load_command *)seg);
		if ((long)seg - (long)mapped > g_cfsize)
			fatal_err("corrupted");
	}
	return (get_text_sect32(seg, buf, (void *)mapped));
}

int			get_text(t_text *buf, t_mach_header *mapped)
{
	int ret;

	if (g_file_type == archx64)
		ret = get_text64(buf, mapped);
	else
		ret = get_text32(buf, mapped);
	if (!ret && (long)(buf->text) + (long)(buf->size) - (long)mapped > g_cfsize)
		fatal_err("corrupted");
	return (ret);
}
