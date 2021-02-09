/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:53:32 by tyasmine          #+#    #+#             */
/*   Updated: 2019/11/24 16:08:54 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	spec_u(t_f *str)
{
	if (str->dlin == 1)
		str->pp = (unsigned short int)va_arg(str->ap, unsigned int);
	else if (str->dlin == 2)
		str->pp = (unsigned char)va_arg(str->ap, unsigned int);
	else if (str->dlin == 3)
		str->pp = va_arg(str->ap, unsigned long int);
	else if (str->dlin == 4)
		str->pp = va_arg(str->ap, unsigned long long int);
	else
		str->pp = va_arg(str->ap, unsigned int);
	spec_u_o_x(str);
}

void	spec_d(t_f *str)
{
	if (str->f[str->i] == 'b')
		str->p = va_arg(str->ap, long long int);
	else if (str->dlin == 1)
		str->p = (short int)va_arg(str->ap, int);
	else if (str->dlin == 2)
		str->p = (signed char)va_arg(str->ap, int);
	else if (str->dlin == 3)
		str->p = va_arg(str->ap, long int);
	else if (str->dlin == 4)
		str->p = va_arg(str->ap, long long int);
	else
		str->p = va_arg(str->ap, int);
	if (str->f[str->i] == 'b')
	{
		str->s = ft_itoa_base16(str->p, 2, 1);
		spec_u_u(str);
	}
	else
		past_d(str);
}

void	spec(t_f *str)
{
	if (str->shir == -1)
		str->shir = va_arg(str->ap, int);
	if (str->toch == -1)
		str->toch = va_arg(str->ap, int);
	if (str->f[str->i] == '%')
		spec_prc(str);
	else if (str->f[str->i] == 'c' || str->f[str->i] == 's')
		spec_cs(str);
	else if (str->f[str->i] == 'p')
		spec_p(str);
	else if (str->f[str->i] == 'd' ||
			str->f[str->i] == 'i' || str->f[str->i] == 'b')
		spec_d(str);
	else if (str->f[str->i] == 'u' || str->f[str->i] == 'o' ||
			str->f[str->i] == 'x' || str->f[str->i] == 'X')
		spec_u(str);
	else if (str->f[str->i] == 'f')
	{
		if ((!str->t))
			str->toch = 6;
		if (!str->shir)
			str->shir = -1;
		str->iter += ft_parse_float(str->ap, str);
	}
}

void	spec_format(t_f *str)
{
	str->i++;
	if (str->f[str->i])
	{
		flag(str);
		shir(str);
		toch(str);
		dlin(str);
		spec(str);
	}
}

int		ft_printf(char *format, ...)
{
	t_f	str;

	va_start(str.ap, format);
	str.f = format;
	str.i = 0;
	str.iter = 0;
	while (str.f[str.i])
	{
		if ((str.f[str.i] == '%') && (str.f[str.i + 1] != '\0'))
		{
			list_null(&str);
			spec_format(&str);
		}
		else if (str.f[str.i] != '%' && (str.f[str.i] != '\0'))
			ft_putchar_p(str.f[str.i], &str);
		if (str.f[str.i] != '\0')
			str.i++;
	}
	va_end(str.ap);
	return (str.iter);
}
