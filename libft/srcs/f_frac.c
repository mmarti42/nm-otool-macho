/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_frac.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 05:29:55 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/21 05:29:58 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_pow	*exponentation5(int exp)
{
	int		size;
	char	*new;
	t_pow	*lst;

	exp = -exp;
	size = exp * LG5 + exp / 0.85 / 4 + 1;
	if (!(new = (char *)ft_memalloc(size)))
		exit(123);
	if (!(lst = (t_pow *)ft_memalloc(sizeof(t_pow))))
		exit(123);
	lst->size = size;
	new[size - 1] = 1;
	while (exp--)
		tutu(new, size, 5);
	lst->num = new;
	return (lst);
}

void	get_pow5_list(t_pow *lst, char *mantissa, int exp)
{
	while (*mantissa)
	{
		if (*mantissa == '1')
		{
			lst->next = exponentation5(exp);
			lst = lst->next;
		}
		mantissa++;
		exp--;
	}
}

void	add_frac(char *a, char *b, int bsize)
{
	int i;

	i = -1;
	while (++i < bsize)
		a[i] += *b++;
}

t_pow	*sum_frac(t_pow *lst)
{
	t_pow	*res;
	char	*res_num;
	int		len;

	len = get_last(lst)->size;
	if (!(res = ft_memalloc(sizeof(t_pow))))
		exit(123);
	if (!(res_num = ft_memalloc(len)))
		exit(123);
	while (lst)
	{
		add_frac(res_num, lst->num, lst->size);
		carry(res_num, len);
		lst = lst->next;
	}
	res->num = res_num;
	res->size = len;
	return (res);
}

t_pow	*get_frac(char *mantissa, int exp)
{
	t_pow *lst;
	t_pow *tmp;
	t_pow *res;

	while (*mantissa && *mantissa != '1')
	{
		mantissa++;
		exp--;
	}
	if (*mantissa)
		lst = exponentation5(exp);
	else
		return (0);
	get_pow5_list(lst, mantissa + 1, --exp);
	tmp = lst;
	res = sum_frac(tmp);
	ft_free_pow(lst);
	return (res);
}
