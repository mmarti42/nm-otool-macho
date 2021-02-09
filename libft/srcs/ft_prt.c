/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:57:15 by tyasmine          #+#    #+#             */
/*   Updated: 2019/11/23 20:13:24 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	list_null(t_f *str)
{
	str->f_min = 0;
	str->f_plus = 0;
	str->f_prob = 0;
	str->f_sharp = 0;
	str->f_null = 0;
	str->shir = 0;
	str->toch = 0;
	str->dlin = 0;
	str->a = 0;
	str->t = 0;
	str->p = 0;
	str->s = 0;
	str->tmp = 0;
	str->her = 0;
}

int		ft_nbr_len(long long int n)
{
	int i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}
