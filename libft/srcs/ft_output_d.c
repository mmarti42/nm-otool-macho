/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:45:58 by tyasmine          #+#    #+#             */
/*   Updated: 2019/11/23 20:11:51 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	past_db(t_f *str)
{
	if (str->f_null && str->toch < str->a)
	{
		str->toch += str->shir;
		str->shir = 0;
	}
}

void	past_dc(t_f *str)
{
	if (str->f_prob && str->p >= 0 && !(str->f_plus))
	{
		ft_putchar_p(' ', str);
		if (str->f_min || (str->f_min && str->f_null))
			str->shir -= 1;
		else
			str->toch -= 1;
	}
}

void	past_ddd(t_f *str)
{
	if (str->toch >= str->a)
		str->shir -= str->toch;
	else if (str->f_null && str->toch < str->a)
		past_db(str);
	else if (str->p != 0 || (str->f_sharp && (str->p != 0 ||
	str->f[str->i] == 'o')) || (str->p == 0 && !(str->t) &&
	(str->f_plus || str->f_prob || str->shir)))
		str->shir -= str->a;
	while (str->shir-- > 0)
	{
		ft_putchar_p(' ', str);
		str->f_prob = 0;
	}
	if (str->f_prob && (str->p >= 0) && !(str->f_plus))
		past_dc(str);
	if (str->f_plus)
		ft_putchar_p('+', str);
	if (str->p < 0 && (str->t || str->f_null))
		ft_putchar_p('-', str);
	if (str->toch > str->a)
		past_da(str);
	ft_putnbr_p(str->p, str);
}

void	past_dd(t_f *str)
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
		if (!(str->f_min && str->f_null && str->p == 0))
			ft_putnbr_p(str->p, str);
		if (str->toch >= str->a)
			str->shir -= str->toch;
		else if (str->p != 0 || (str->f_sharp && (str->p != 0 ||
		str->f[str->i] == 'o')) || (str->p == 0 && !(str->t) &&
		(str->f_min || str->f_prob)))
			str->shir -= str->a;
		while (str->shir-- > 0)
			ft_putchar_p(' ', str);
	}
	else
		past_ddd(str);
}

void	past_d(t_f *str)
{
	if (str->f_min && str->f_null)
		str->f_null = 0;
	str->a = ft_nbr_len(str->p);
	if (str->f_plus && str->p < 0)
		str->f_plus = 0;
	if (str->p < 0 || str->f_plus)
		str->shir -= 1;
	if (str->f_null && str->t)
		str->f_null = 0;
	if (str->shir <= str->toch)
	{
		if (str->f_prob && str->p >= 0 && !(str->f_plus))
			ft_putchar_p(' ', str);
		if (str->f_plus)
			ft_putchar_p('+', str);
		if (str->p < 0 && str->t)
			ft_putchar_p('-', str);
		if (str->toch > str->a)
			past_da(str);
		ft_putnbr_p(str->p, str);
	}
	else if (str->shir > str->toch)
		past_dd(str);
}
