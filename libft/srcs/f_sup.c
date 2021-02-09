/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 05:19:24 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/21 05:19:25 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_pow		*get_last(t_pow *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int			add_digit(int tmp, int digit)
{
	tmp *= 10;
	return (tmp + digit);
}

void		carry(char *num, int size)
{
	while (--size)
	{
		if (num[size] > 9)
		{
			num[size - 1] += num[size] / 10;
			num[size] %= 10;
		}
	}
}

void		tutu(char *num, int size, int pow)
{
	int tmp;

	tmp = size;
	while (--tmp >= 0)
		num[tmp] *= pow;
	carry(num, size);
}

t_pow		*division(char *num, int divider, int size)
{
	size_t	len;
	int		tmp;
	char	*res;
	int		i;
	t_pow	*lst;

	i = 0;
	tmp = *num;
	len = size;
	while (tmp < divider && len--)
		tmp = add_digit(tmp, *(++num));
	if (!(lst = ft_memalloc(sizeof(t_pow))))
		exit(123);
	lst->size = len;
	if (!(res = ft_memalloc(len)))
		exit(123);
	while (len--)
	{
		res[i++] = tmp / divider;
		tmp = add_digit(tmp % divider, *(++num));
	}
	lst->num = res;
	return (lst);
}
