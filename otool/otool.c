#include "otool.h"

int get_text64(t_text *buf, t_mach_header *mapped)
{
	struct segment_command_64 *seg;
	struct section_64 *sect;
	uint32_t i;

	i = 0;
	seg = (struct segment_command_64 *)get_lc(LC_SEGMENT_64, mapped);
	while (1)
	{
		if (!seg)
			return -1;
		if (!ft_strcmp(seg->segname, "__TEXT"))
			break;
		seg = (struct segment_command_64 *)next_com((t_load_command *)seg);
	}
	sect = (struct section_64 *)((char *)seg + sizeof(struct segment_command_64));
	while (i++ < seg->nsects)
	{
		if (!ft_strcmp(sect->sectname, "__text"))
		{
			buf->text = (char *)mapped + sect->offset;
			buf->size = sect->size;
			return 0;
		}
		sect++;
	}
	return -1;
}

int get_text32(t_text *buf, t_mach_header *mapped)
{
	struct segment_command *seg;
	struct section *sect;
	uint32_t i;

	i = 0;
	seg = (struct segment_command *)get_lc(LC_SEGMENT, mapped);
	while (1)
	{
		if (!seg)
			return -1;
		if (!ft_strcmp(seg->segname, "__TEXT"))
			break;
		seg = (struct segment_command *)next_com((t_load_command *)seg);
	}
	sect = (struct section *)((char *)seg + sizeof(struct segment_command));
	while (i++ < seg->nsects)
	{
		if (!ft_strcmp(sect->sectname, "__text"))
		{
			buf->text = (char *)mapped + sect->offset;
			buf->size = sect->size;
			return 0;
		}
		sect++;
	}
	return -1;
}

int	get_text(t_text *buf, t_mach_header *mapped)
{
	if (g_file_type == archx64)
		return get_text64(buf, mapped);
	else
		return get_text32(buf, mapped);
}

void print_text(const unsigned char *text, size_t size)
{
	if (!size)
		return;
	while (size > 16)
	{
		ft_printf("%016llx ", text);
		ft_printf("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n", text[0], text[1], text[3], text[4]\
		 ,text[5], text[6], text[7], text[8], text[9], text[10], text[11]\
		 ,text[12], text[13], text[14], text[15]);
		 text += 16;
		 size -= 16;
	}
	if (!size)
		return;
	ft_printf("%016llx ", text);
	while (size)
	{
		ft_printf("%02x ", *text);
		size--;
		text++;
	}
	ft_putchar('\n');
}

void print_text_sect(char *fname)
{
	t_mach_header	*mapped;
	t_text 			text;
	t_mach_header	*mapped_tmp;

	ft_bzero(&text, sizeof(t_text));
	if (!(mapped = (t_mach_header *)ft_mmap(fname)))
		return ;
	mapped_tmp = mapped;
	if (*(uint32_t *)mapped == FAT_CIGAM)
		mapped = handle_fat(mapped);
	if (mapped->magic != MH_MAGIC && mapped->magic != MH_MAGIC_64)
		ft_putstr_fd("The file was not recognized as a valid object file\n", STDERR_FILENO);
	else
	{
		g_file_type = mapped->magic;
		if (get_text(&text, mapped) < 0)
			ft_putstr_fd("Can't find text sect\n", STDERR_FILENO);
		print_text((const unsigned char *)text.text, text.size);
	}
	if (munmap(mapped_tmp, g_cfsize) < 0)
		return (fatal_err(strerror(errno)));
}

int main(int ac, char **av)
{
	(void)ac;
	if (ac < 2)
		ft_printf("usage: %s\n", USAGE);
	else {
		if (G_CPU < 0)
			ft_printf("\\u001b[34mWarning\\u001b[34m: unknown host cpu type\n");
		while (*av)
			print_text_sect(*av++);
	}
	return (0);
}