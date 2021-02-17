#include "otool.h"

void print_text_sect(char *fname)
{
	if (!(mapped = (t_mach_header *)ft_mmap(filename)))
		return ;
	if (mapped->magic != MH_MAGIC && mapped->magic != MH_MAGIC_64)
		ft_putstr_fd("The file was not recognized as a valid object file\n", STDERR_FILENO);
}

int main(int ac, char **av)
{
	(void)ac;
	if (ac < 2)
		ft_printf("%s\n", USAGE);
	if (G_CPU < 0)
		ft_printf("\\u001b[34mWarning\\u001b[34m: unknown type of host cpu type\n");
	while (*av)
		print_text_sect(*av++);
	return (0);
}