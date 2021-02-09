/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:44:31 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/21 11:44:32 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_parse_float(va_list vaptr, t_f *list)
{
	long double a;

	if (list->dlin == 5)
		a = va_arg(vaptr, long double);
	else
		a = va_arg(vaptr, double);
	return (dtoi(a, list));
}
