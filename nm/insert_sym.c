#include "nm.h"

t_symbol *not_sort(t_symbol *new, t_symbol *first)
{
	t_symbol *it;

	it = first;
	while (it->next)
		it = it->next;
	it->next = new;
	return first;
}

t_symbol *insert_sym(t_symbol *new, t_symbol *first)
{
	t_symbol *it;

	if (!first)
		return (new);
	if (g_opt.p)
		return not_sort(new, first);
	it = first;
	if (ft_strcmp(new->name, it->name) < 0)
	{
		it->prev = new;
		new->next = it;
		return (new);
	}
	while (ft_strcmp(new->name, it->name) > 0)
	{
		if (!it->next)
		{
			it->next = new;
			new->prev = it;
			return first;
		}
		it = it->next;
	}
	new->prev = it->prev;
	it->prev->next = new;
	it->prev = new;
	new->next = it;
	return (first);
}
