/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_spec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:47:52 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/21 15:47:54 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*check(char *str)
{
	static char *inf = "1111111111111111";

	if (!strncmp(inf, str + 1, 15))
	{
		if (*(str + 16) == '1' && !ft_strchr(str + 17, '1'))
			return ("inf");
		else
			return ("nan");
	}
	return (0);
}

void	handle_w_spec(t_f *format, int len)
{
	int		tmp;
	char	a;

	a = ' ';
	tmp = format->shir;
	while (tmp-- > len)
		ft_putchar(a);
}

void	handle_fl_spec(t_f *format, char c, int *len)
{
	if (c || format->f_plus || format->f_prob)
		(*len)++;
	if (format->shir < *len || format->f_min)
		c ? ft_putchar('-') : 0;
	if (format->f_prob && !c)
		ft_putchar(' ');
	if (*len < format->shir && !format->f_min)
	{
		handle_w_spec(format, *len);
		c ? ft_putchar('-') : 0;
		*len = format->shir;
	}
}
