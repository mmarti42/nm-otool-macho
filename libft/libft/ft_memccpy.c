/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:19:22 by tyasmine          #+#    #+#             */
/*   Updated: 2019/04/23 02:56:23 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	str1 = (char *)dst;
	str2 = (char *)src;
	i = 0;
	while (i < n)
	{
		str1[i] = str2[i];
		if (str2[i] == (char)c)
			return ((void *)dst);
		i++;
	}
	return ((void *)NULL);
}
