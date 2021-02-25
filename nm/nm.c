/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:02:11 by mmarti            #+#    #+#             */
/*   Updated: 2021/02/25 20:02:13 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		free_sym_list(t_symbol *symlist)
{
	t_symbol *tmp;

	while (symlist)
	{
		tmp = symlist;
		symlist = symlist->next;
		free(tmp);
	}
}

static char	**ft_nm_getopt(const char **av)
{
	char	buf[6];
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

int			main(int ac, char **av)
{
	char **args;

	(void)ac;
	if (G_CPU < 0)
		ft_printf("\\u001b[34mWarning\\u001b[34m: unknown host cpu type\n");
	args = ft_nm_getopt((const char **)av);
	if (!*args)
		print_symtab("a.out");
	else
	{
		while (*args)
		{
			if (args[1])
				ft_putchar('\n');
			print_symtab(*args++);
		}
	}
	return (0);
}
