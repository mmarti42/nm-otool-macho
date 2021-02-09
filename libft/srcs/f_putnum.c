/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_putnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 08:51:18 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/21 08:51:22 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	lenhandle(t_f *format, int len)
{
	int		tmp;
	char	a;

	a = ' ';
	if (format->f_null && !format->f_min)
		a = '0';
	tmp = format->shir;
	while (tmp-- > len)
		ft_putchar(a);
}

void	flhandle(t_f *format, int *len, t_res res)
{
	if (res.sign || format->f_plus || format->f_prob)
		(*len)++;
	if (format->f_null)
	{
		res.sign == 1 ? ft_putchar('-') : 0;
		if (format->f_plus && res.sign == 0)
			ft_putchar('+');
		else if (format->f_prob && !res.sign)
			ft_putchar(' ');
	}
	if (*len < format->shir && !format->f_min)
	{
		lenhandle(format, *len);
		*len = format->shir;
	}
	if (!format->f_null)
		res.sign == 1 ? ft_putchar('-') : 0;
	if (format->f_plus && res.sign == 0 && !format->f_null)
		ft_putchar('+');
	else if (format->f_prob && res.sign == 0 && !format->f_null)
		ft_putchar(' ');
}

void	ft_putnum2(t_res res, int precision)
{
	while (*res.num && precision >= 0)
	{
		ft_putchar(*res.num++);
		precision--;
	}
	while (precision >= 0)
	{
		ft_putchar('0');
		precision--;
	}
}

int		ft_putnum(t_res res, int precision, t_f *format)
{
	int len;

	len = precision + res.entirelen;
	if (precision || format->f_sharp)
		len++;
	flhandle(format, &len, res);
	while (*res.num != '.')
		ft_putchar(*res.num++);
	if (precision || format->f_sharp)
		ft_putnum2(res, precision);
	if (format->f_min && format->shir > len)
		lenhandle(format, len);
	return (len);
}
