/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:56:18 by tyasmine          #+#    #+#             */
/*   Updated: 2019/11/23 20:04:29 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	past_da(t_f *str)
{
	if ((str->f[str->i] == 'x' || str->f[str->i] == 'X')
			&& str->f_sharp && str->p != 0)
	{
		if (str->f[str->i] == 'x')
			ft_putstr_p("0x", str);
		else if (str->f[str->i] == 'X')
			ft_putstr_p("0X", str);
		if (!(str->t))
			str->toch -= 2;
		if (str->f_min)
			str->shir -= 2;
	}
	while (str->toch > str->a)
	{
		if (str->her == 0)
			ft_putchar_p('0', str);
		if (str->f_min && str->f_null && str->p == 0)
		{
			ft_putchar_p(' ', str);
			str->her = 1;
		}
		str->toch--;
		str->shir--;
	}
}

void	past_x(t_f *str)
{
	ft_putchar_p('0', str);
	if (str->f[str->i] == 'x')
		ft_putchar_p('x', str);
	else if (str->f[str->i] == 'X')
		ft_putchar_p('X', str);
	if (str->shir > str->toch && (str->f_min || (str->f_min && str->f_null)))
	{
		if (str->f[str->i] == 'X' || str->f[str->i] == 'x')
			str->shir -= 1;
		str->shir -= 1;
	}
}

void	past_o_o(t_f *str)
{
	if (str->f_prob && (str->p >= 0) && !(str->f_plus))
		past_dc(str);
	if (str->f_plus)
		ft_putchar_p('+', str);
	if (str->p < 0 && (str->t || str->f_null))
		ft_putchar_p('-', str);
	if (str->toch > str->a)
		past_da(str);
	else if (str->f_sharp && !(str->f_null) && (str->toch < str->a))
		past_x(str);
	else if (str->f_sharp && (str->f_null) && str->shir < 0)
		past_x(str);
	ft_putstr_p(str->s, str);
}

void	spec_p_p(t_f *str)
{
	str->shir -= str->a + 2;
	if (str->f_min)
	{
		ft_putstr_p("0x", str);
		while (str->a-- != 0)
			ft_putchar_p(*str->s++, str);
	}
	while (--str->shir >= 0)
		ft_putchar_p(' ', str);
}

void	spec_p(t_f *str)
{
	str->p = (long long int)va_arg(str->ap, void *);
	str->s = ft_itoa_base(str->p, 16);
	str->tmp = str->s;
	str->a = ft_strlen(str->s);
	if (str->shir > str->a)
		spec_p_p(str);
	else if (str->shir == str->a)
	{
		ft_putstr_p("0x", str);
		while (str->a-- != 0 && (!str->t))
			ft_putchar_p(*str->s++, str);
	}
	if (!str->f_min || str->shir < str->a)
	{
		if (!str->f_min || (str->shir < str->a && str->shir > 0))
			ft_putstr_p("0x", str);
		while (--str->a >= 0 && (!str->t))
			ft_putchar_p(*str->s++, str);
	}
	if (*str->tmp != '0')
		free(str->tmp);
}
