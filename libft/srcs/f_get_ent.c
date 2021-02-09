/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_get_ent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 05:15:38 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/21 05:15:40 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_pow	*get_pow2_list(int exp, char *mantissa, t_pow *lst)
{
	int div;

	div = 2;
	while (*mantissa && *mantissa != '1')
	{
		mantissa++;
		exp--;
		div *= 2;
	}
	if (exp < 0 || !*mantissa)
		return (0);
	lst->next = division(lst->num, div, lst->size);
	get_pow2_list(exp - 1, mantissa + 1, lst->next);
	return (lst);
}

t_pow	*exponentation2(int exp)
{
	int		size;
	char	*new;
	t_pow	*lst;

	size = exp * LG2 + 1;
	if (!(new = (char *)ft_memalloc(size)))
		exit(123);
	if (!(lst = (t_pow *)ft_memalloc(sizeof(t_pow))))
		exit(123);
	lst->size = size;
	new[size - 1] = 1;
	while (exp--)
		tutu(new, size, 2);
	lst->num = new;
	return (lst);
}

void	add_num(char *a, char *b, int asize, int bsize)
{
	int blya;

	blya = asize;
	while (bsize)
		a[--asize] += b[--bsize];
	carry(a, blya);
}

t_pow	*get_sum(t_pow *lst)
{
	int		len;
	char	*num;
	t_pow	*res;

	len = lst->size + 1;
	if (!(num = (char *)ft_memalloc(len)))
		exit(123);
	if (!(res = (t_pow *)ft_memalloc(sizeof(t_pow))))
		exit(123);
	res->size = len;
	res->num = num;
	while (lst)
	{
		add_num(num, lst->num, len, lst->size);
		lst = lst->next;
	}
	return (res);
}

t_pow	*get_entire(char *mantissa, int exp)
{
	t_pow *lst;
	t_pow *res;

	if (exp < 0)
		return (0);
	lst = exponentation2(exp);
	get_pow2_list(exp - 1, mantissa + 1, lst);
	res = get_sum(lst);
	ft_free_pow(lst);
	return (res);
}
