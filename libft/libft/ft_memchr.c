/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:24:18 by tyasmine          #+#    #+#             */
/*   Updated: 2019/04/23 02:59:15 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*str;
	char	a;

	i = 0;
	str = (char *)s;
	a = (char)c;
	while (i < n)
	{
		if (str[i] == a)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
