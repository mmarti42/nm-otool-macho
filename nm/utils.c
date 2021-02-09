#include "nm.h"

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

char **ft_nm_getopt(const char **av)
{
	char 	buf[5];
	int		i;
	char	**ret;

	i = -1;
	if (!(ret = parse_opt(av, "pruA", buf)))
		fatal_err(USAGE);
	while (buf[++i])
	{
		if (*buf == 'p')
			g_opt.p = true;
		else if (*buf == 'u')
			g_opt.u = true;
		else if (*buf == 'A')
			g_opt.a = true;
		else if (*buf == 'r')
			g_opt.r = true;
	}
	return (ret);
}