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

void fatal_err(const char *mes)
{
	if (mes)
		ft_putstr_fd(mes, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(1);
}

void *xmalloc(size_t size)
{
	void *ptr;

	if (!(ptr = malloc(size)))
		fatal_err(strerror(errno));
	return ft_memset(ptr, 0, size);
}

t_load_command *next_com(t_load_command *ld)
{
	return (t_load_command *)((char *)ld + ld->cmdsize);
}

void *get_lc(uint32_t cmd, t_mach_header *mapped)
{
	uint32_t		i;
	t_load_command	*ld;

	i = 0;
	if (g_file_type == archx86)
		ld = (t_load_command *)((char *)mapped + sizeof(struct mach_header));
	else if (g_file_type == archx64)
		ld = (t_load_command *)((char *)mapped + sizeof(struct mach_header_64));
	while (++i <= mapped->ncmds)
	{
		if ((char *)ld - (char *)mapped + ld->cmdsize >= g_cfsize)
			fatal_err("corrupted");
		if (ld->cmd == cmd)
			return ld;
		ld = next_com(ld);
	}
	return NULL;
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
