/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:02:01 by tyasmine          #+#    #+#             */
/*   Updated: 2019/04/23 03:13:25 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memalloc(size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	while (i < size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
