/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:46:10 by tyasmine          #+#    #+#             */
/*   Updated: 2019/11/24 15:52:24 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	flag(t_f *str)
{
	while (str->f[str->i])
	{
		if (str->f[str->i] == '-')
			str->f_min = 1;
		else if (str->f[str->i] == '+')
			str->f_plus = 1;
		else if (str->f[str->i] == ' ')
			str->f_prob = 1;
		else if (str->f[str->i] == '#')
			str->f_sharp = 1;
		else if (str->f[str->i] == '0')
			str->f_null = 1;
		else
			break ;
		str->i++;
	}
}

void	shir(t_f *str)
{
	char *s;

	s = &str->f[str->i];
	if (str->f[str->i] == '*')
	{
		str->shir = -1;
		str->i++;
	}
	if (ft_isdigit(str->f[str->i]) == 1)
		str->shir = ft_atoi(s);
	while (ft_isdigit(str->f[str->i]) == 1)
		str->i++;
}

void	toch(t_f *str)
{
	char *s;

	if (str->f[str->i] == '.')
	{
		str->i++;
		if (str->toch == '*')
		{
			str->toch = -1;
			str->i++;
		}
		s = &str->f[str->i];
		str->t = 1;
		if (ft_isdigit(str->f[str->i]) == 1)
			str->toch = ft_atoi(s);
		while (ft_isdigit(str->f[str->i]) == 1)
			str->i++;
	}
}

void	dlin_plus(t_f *str, int x, int h, int l)
{
	if (((h % 2) != 0) && (h != 0) && (x == 0) && (l == 0))
		str->dlin = 1;
	else if (((((l % 2) == 0) && (l != 0)) ||
				((h != 0) && ((l != 0)))) && (x == 0))
		str->dlin = 4;
	else if (((h % 2) == 0) && (h != 0) && (x == 0))
		str->dlin = 2;
	else if (((l % 2) != 0) && (l != 0) && (x == 0))
		str->dlin = 3;
	else if ((x != 0) && (l == 0) && (h == 0))
		str->dlin = 5;
	else if ((x != 0) && ((l != 0) || (h != 0)))
		str->dlin = 6;
}

void	dlin(t_f *str)
{
	int h;
	int l;
	int x;

	x = 0;
	h = 0;
	l = 0;
	while ((str->f[str->i] == 'h') ||
			(str->f[str->i] == 'l') || (str->f[str->i] == 'L'))
	{
		if (str->f[str->i] == 'h')
			h++;
		if (str->f[str->i] == 'l')
			l++;
		if (str->f[str->i] == 'L')
			x++;
		str->i++;
	}
	dlin_plus(str, x, h, l);
}
