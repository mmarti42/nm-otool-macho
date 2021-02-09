/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 18:31:02 by tyasmine          #+#    #+#             */
/*   Updated: 2019/04/23 03:04:35 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (dst[j] != '\0' && j < size)
		j++;
	while (src[i] != '\0' && (j + 1 < size))
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	if (j < size)
		dst[j] = '\0';
	return ((size_t)(ft_strlen(src) + j - i));
}
