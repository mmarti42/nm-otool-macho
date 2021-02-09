/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_sup2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 09:15:33 by mmarti            #+#    #+#             */
/*   Updated: 2019/11/21 09:15:34 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	*ft_ncpy(void *destination, const void *source, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;

	dst = (unsigned char *)destination;
	src = (unsigned char *)source;
	while (n--)
	{
		*dst = *src + 48;
		dst++;
		src++;
	}
	return (destination);
}

char	*fracstr(t_pow *frac)
{
	char *res;

	if (!frac)
		return (ft_strdup(".000000"));
	if (!(res = (char *)ft_memalloc(frac->size + 2)))
		exit(123);
	*res = '.';
	ft_ncpy(res + 1, frac->num, frac->size);
	return (res);
}

char	*entirestr(t_pow *entire)
{
	char *res;
	char *tmp;

	if (!entire)
		return (ft_strdup("0"));
	tmp = entire->num;
	if (!*tmp)
	{
		tmp++;
		entire->size--;
	}
	if (!(res = ft_memalloc(entire->size + 1)))
		exit(123);
	return (ft_ncpy(res, tmp, entire->size));
}

char	*ft_numjoin(t_pow *entire, t_pow *frac)
{
	char *s1;
	char *s2;
	char *res;

	s2 = fracstr(frac);
	s1 = entirestr(entire);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

int		entlen(char *num)
{
	int res;

	res = 0;
	while (*num != '.')
	{
		num++;
		res++;
	}
	return (res);
}
