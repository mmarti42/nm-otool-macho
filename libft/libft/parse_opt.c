#include "libft.h"

/*
** buf должен быть не менее strlen(opt_list) + 1
** При ошибке возвращает NULL
*/

static char get_opt(char const *av, char const *opt_list, char *buf)
{
	while (*++av)
	{
		if (!ft_strchr(opt_list, *av))
			return (*av);
		if (!ft_strchr(buf, *av))
			buf[ft_strlen(buf)] = *av;
	}
	return (0);
}

char		**parse_opt(char const **av, char const *opt_list, char *buf)
{
	char	err;
	int		i;

	i = 0;
	ft_bzero(buf, ft_strlen(opt_list) + 1);
	while (av[++i])
	{
		if (av[i][0] == '-' && ft_isalpha(av[i][1]))
		{
			if ((err = get_opt(av[i], opt_list, buf)) != 0)
			{
				ft_putstr_fd(av[0], STDERR_FILENO);
				ft_putstr_fd(": illegal option: ", STDERR_FILENO);
				ft_putchar_fd(err, STDERR_FILENO);
				ft_putchar_fd('\n', STDERR_FILENO);
				return NULL;
			}
		}
		else
			break ;
	}
	return (char **)av + i;
}
