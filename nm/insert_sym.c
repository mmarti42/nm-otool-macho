/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_sym.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 20:31:26 by mmarti            #+#    #+#             */
/*   Updated: 2021/02/25 20:31:27 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_symbol	*not_sort(t_symbol *new, t_symbol *first)
{
	t_symbol *it;

	it = first;
	while (it->next)
		it = it->next;
	it->next = new;
	return (first);
}

static t_symbol	*push_begin(t_symbol *new, t_symbol *first)
{
	first->prev = new;
	new->next = first;
	return (new);
}

t_symbol		*ins(t_symbol *new, t_symbol *it, t_symbol *first)
{
	new->prev = it->prev;
	if (it->prev)
		it->prev->next = new;
	it->prev = new;
	new->next = it;
	return (first);
}

t_symbol		*insert_sym(t_symbol *new, t_symbol *first)
{
	t_symbol	*it;
	int			cmp;

	if (!first)
		return (new);
	if (g_opt.p)
		return (not_sort(new, first));
	if (ft_strcmp(new->name, first->name) < 0)
		return (push_begin(new, first));
	it = first;
	while ((cmp = ft_strcmp(new->name, it->name)) >= 0)
	{
		if (cmp == 0 && it->type == 'I')
			break ;
		if (!it->next)
		{
			it->next = new;
			new->prev = it;
			return (first);
		}
		it = it->next;
	}
	return (ins(new, it, first));
}
