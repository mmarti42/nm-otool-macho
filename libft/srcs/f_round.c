/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_round.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 09:19:04 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/21 09:19:05 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	entireround(char *tmp)
{
	if (*(tmp + 1) > '5')
		*(tmp - 1) += 1;
	else if (*(tmp + 1) < '5')
		return ;
	else
	{
		if (*(tmp - 1) + 1 % 2 == 0)
			*(tmp - 1) += 1;
		else
			*(tmp - 1) -= 1;
	}
}

void	carry_str(char *num, int size)
{
	while (--size)
	{
		if (num[size] > '9')
		{
			num[size] -= 48;
			num[size] -= 10;
			num[size] += 48;
			if (num[size - 1] == '.')
				size--;
			num[size - 1] += 1;
		}
	}
}

void	ft_round(char *num, int precision)
{
	char	*tmp;
	int		len;

	tmp = ft_strchr(num, '.');
	if (!precision)
		return (entireround(tmp));
	len = ft_strlen(tmp + 1);
	if (precision >= len)
		return ;
	if (tmp[precision + 1] > '4')
		tmp[precision] += 1;
	carry_str(num, ft_strlen(num));
}
