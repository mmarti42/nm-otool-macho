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