/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_lst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 09:41:02 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/23 19:53:24 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

long	ft_pow2(int pow)
{
	int a;

	a = 1;
	while (pow--)
		a *= 2;
	return (a);
}

void	ft_free_pow(t_pow *lst)
{
	t_pow *tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->num);
		free(tmp);
	}
}

void	ft_free_vars(t_vars vars)
{
	if (vars.entire)
		ft_free_pow(vars.entire);
	if (vars.frac)
		ft_free_pow(vars.frac);
}

t_f		*new_format(void)
{
	t_f *list;

	if (!(list = (t_f *)ft_memalloc(sizeof(t_f))))
		exit(123);
	list->toch = -1;
	list->shir = -1;
	return (list);
}
