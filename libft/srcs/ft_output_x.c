/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:52:21 by tyasmine          #+#    #+#             */
/*   Updated: 2019/11/23 20:15:46 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	past_ooo(t_f *str)
{
	if (str->toch >= str->a)
		str->shir -= str->toch;
	else if (str->f_null && str->toch < str->a)
		past_db(str);
	else if (str->p != 0 || (str->p == 0 && !(str->t) &&
			(str->f_plus || str->f_prob || str->shir)))
		str->shir -= str->a;
	if (str->f_sharp && !(str->f_null) &&
		((str->toch < str->a) || (str->f[str->i] != 'o')))
		str->shir -= 1;
	if ((str->f[str->i] == 'x' || str->f[str->i] == 'X') && str->f_sharp)
		str->shir -= 1;
	while (str->shir-- > 0)
	{
		ft_putchar_p(' ', str);
		str->f_prob = 0;
	}
	past_o_o(str);
}

void	past_oo(t_f *str)
{
	if (str->f_min || (str->f_min && str->f_null))
	{
		if (str->f_plus)
			ft_putchar_p('+', str);
		if (str->f_null && str->toch < str->a)
			past_db(str);
		if (str->p < 0 && (str->t || str->f_null))
			ft_putchar_p('-', str);
		if (str->f_prob && str->p >= 0 && !(str->f_plus))
			past_dc(str);
		if (str->toch > str->a)
			past_da(str);
		if (str->f_sharp && !(str->f_null) && (str->toch < str->a))
			past_x(str);
		ft_putstr_p(str->s, str);
		if (str->toch >= str->a)
			str->shir -= str->toch;
		else if (str->p != 0 || (str->p == 0 &&
				!(str->t) && (str->f_min || str->f_prob)))
			str->shir -= str->a;
		while (str->shir-- > 0)
			ft_putchar_p(' ', str);
	}
	else
		past_ooo(str);
}

void	past_o(t_f *str)
{
	if (str->f_min && str->f_null)
		str->f_null = 0;
	if (str->f_plus && str->p < 0)
		str->f_plus = 0;
	if (str->p < 0 || str->f_plus)
		str->shir -= 1;
	if (str->f_null && str->t)
		str->f_null = 0;
	if (str->shir <= str->toch)
	{
		str->shir = 0;
		if (str->f_prob && str->p >= 0 && !(str->f_plus))
			ft_putchar_p(' ', str);
		if (str->f_plus)
			ft_putchar_p('+', str);
		if (str->p < 0 && str->t)
			ft_putchar_p('-', str);
		if (str->toch > str->a)
			past_da(str);
		if (str->f_sharp && str->shir >= 0 && !(str->f_null))
			past_x(str);
		ft_putstr_p(str->s, str);
	}
	else if (str->shir > str->toch)
		past_oo(str);
}

void	spec_u_u(t_f *str)
{
	str->tmp = str->s;
	str->a = ft_strlen(str->s);
	if (str->s[0] == '0' && str->a == 1)
	{
		str->p = 0;
		past_d(str);
	}
	else
	{
		str->p = 1;
		past_o(str);
		free(str->tmp);
	}
}

void	spec_u_o_x(t_f *str)
{
	if (str->f[str->i] == 'o')
	{
		str->s = ft_itoa_base16(str->pp, 8, 1);
		spec_u_u(str);
	}
	else if (str->f[str->i] == 'u')
	{
		str->s = ft_itoa_base16(str->pp, 10, 1);
		spec_u_u(str);
	}
	else
	{
		if (str->f[str->i] == 'x')
			str->s = ft_itoa_base16(str->pp, 16, 1);
		else if (str->f[str->i] == 'X')
			str->s = ft_itoa_base16(str->pp, 16, 0);
		spec_u_u(str);
	}
}
