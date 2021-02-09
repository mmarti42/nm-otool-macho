/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 18:00:30 by tyasmine          #+#    #+#             */
/*   Updated: 2019/04/23 03:07:00 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *hsk, const char *ndl, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (!(*ndl))
		return ((char *)hsk);
	while (i <= len)
	{
		j = 0;
		while ((hsk[i + j] == ndl[j] || ndl[j] == '\0')
				&& (i + j <= len))
		{
			if (ndl[j] == '\0')
				return ((char *)hsk + i);
			j++;
		}
		i++;
	}
	return (0);
}
