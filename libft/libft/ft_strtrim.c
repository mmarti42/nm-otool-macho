/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:47:07 by tyasmine          #+#    #+#             */
/*   Updated: 2019/04/23 03:17:29 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_stri(char const *c)
{
	int b;

	b = 0;
	while (c[b] == ' ' || c[b] == '\n' || c[b] == '\t')
		b++;
	return (b);
}

char		*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		l;
	int		a;

	a = 0;
	str = "";
	if (!s)
		return ((char *)s);
	i = ft_stri(s);
	l = ft_strlen(s);
	while (s[l - 1] == ' ' || s[l - 1] == '\n' || s[l - 1] == '\t')
		l--;
	if (l == 0)
		return (str);
	if (!(str = (char *)malloc(sizeof(char) * (l + 1 - i))))
		return (NULL);
	while (i != l)
	{
		str[a] = s[i];
		i++;
		a++;
	}
	str[a] = '\0';
	return (str);
}
