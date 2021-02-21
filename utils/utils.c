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
