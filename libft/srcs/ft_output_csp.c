/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_csp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:52:05 by tyasmine          #+#    #+#             */
/*   Updated: 2019/11/23 20:01:22 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	spec_prc(t_f *str)
{
	str->a = 1;
	if (str->shir > str->a && !(str->f_min))
	{
		if (str->f_null)
		{
			while (str->shir-- > str->a)
				ft_putchar_p('0', str);
		}
		else
			while (str->shir-- > str->a)
				ft_putchar_p(' ', str);
	}
	ft_putchar_p('%', str);
	if (str->f_min)
		while (str->shir-- > str->a)
			ft_putchar_p(' ', str);
}

void	pastc(t_f *str)
{
	unsigned char c;

	if (str->shir)
	{
		if (str->f_min)
		{
			c = (unsigned char)va_arg(str->ap, int);
			ft_putchar_p((char)c, str);
		}
		while (--str->shir)
			ft_putchar_p(' ', str);
	}
}

void	pasts(t_f *str)
{
	str->shir -= str->a;
	if (str->f_min)
	{
		while (str->a-- != 0)
			ft_putchar_p(*str->s++, str);
	}
	while (str->shir-- != 0)
	{
		if (str->f_null && !str->f_min)
			ft_putchar_p('0', str);
		else
			ft_putchar_p(' ', str);
	}
	if (!str->f_min)
		while (str->a-- != 0)
			ft_putchar_p(*str->s++, str);
}

void	spec_cs(t_f *str)
{
	unsigned char c;

	if ((str->f_min || str->shir) && str->f[str->i] == 'c')
		pastc(str);
	if (str->f[str->i] == 'c' && !(str->f_min))
	{
		c = (unsigned char)va_arg(str->ap, int);
		ft_putchar_p((char)c, str);
	}
	else if (str->f[str->i] == 's')
	{
		str->s = va_arg(str->ap, char *);
		if (str->t == 1 && str->toch == 0)
			str->s = "";
		if (str->s == NULL)
			str->s = "(null)";
		str->a = ft_strlen(str->s);
		if (str->a > str->toch && str->toch)
			str->a = str->toch;
		if (str->shir > str->a)
			pasts(str);
		else
			while (str->a-- != 0)
				ft_putchar_p(*str->s++, str);
	}
}

size_t	digit_count(unsigned long nb, int base)
{
	size_t i;

	i = 0;
	while (nb)
	{
		nb /= base;
		i++;
	}
	return (i);
}
