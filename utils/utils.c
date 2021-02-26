/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:55:54 by mmarti            #+#    #+#             */
/*   Updated: 2021/02/25 20:55:55 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void			*ft_mmap(char *filename)
{
	int			fd;
	char		*mapped;
	struct stat	st;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar('\n');
		close(fd);
		return (NULL);
	}
	if (fstat(fd, &st) < 0)
		fatal_err(strerror(errno));
	if ((g_cfsize = st.st_size) < (long long)sizeof(t_mach_header))
	{
		ft_putstr_fd("not binary\n", STDERR_FILENO);
		return (NULL);
	}
	if ((mapped = mmap(NULL, st.st_size, PROT_READ,
	MAP_SHARED, fd, 0)) == MAP_FAILED)
		fatal_err(strerror(errno));
	close(fd);
	return (mapped);
}

void			fatal_err(const char *mes)
{
	if (mes)
		ft_putstr_fd(mes, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(1);
}

void			*xmalloc(size_t size)
{
	void *ptr;

	if (!(ptr = malloc(size)))
		fatal_err(strerror(errno));
	return (ft_memset(ptr, 0, size));
}

t_load_command	*next_com(t_load_command *ld)
{
	return ((t_load_command *)((char *)ld + ld->cmdsize));
}

void			*get_lc(uint32_t cmd, t_mach_header *mapped)
{
	uint32_t		i;
	t_load_command	*ld;

	i = 0;
	if (g_file_magic == archx86)
		ld = (t_load_command *)((char *)mapped + sizeof(struct mach_header));
	else if (g_file_magic == archx64)
		ld = (t_load_command *)((char *)mapped + sizeof(struct mach_header_64));
	while (++i <= mapped->ncmds)
	{
		if ((char *)ld - (char *)mapped + ld->cmdsize >= g_cfsize)
			fatal_err("corrupted");
		if (ld->cmd == cmd)
			return (ld);
		ld = next_com(ld);
	}
	return (NULL);
}
