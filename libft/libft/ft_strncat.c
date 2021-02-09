/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:59:30 by tyasmine          #+#    #+#             */
/*   Updated: 2019/04/23 03:04:05 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		a;
	int		b;

	i = 0;
	a = 0;
	b = 0;
	while (s1[a] != '\0')
		a++;
	while (s2[b] != '\0')
	{
		if (i < n)
		{
			s1[a + b] = s2[b];
			b++;
			i++;
		}
		else
			break ;
	}
	s1[a + b] = '\0';
	return (s1);
}
