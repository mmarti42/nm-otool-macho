/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:03:14 by tyasmine          #+#    #+#             */
/*   Updated: 2019/04/23 03:09:29 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	long long int i;
	long long int sign;
	long long int res;
	long long int j;

	i = 0;
	sign = 0;
	res = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	(str[i] == '-') ? sign = 1 : (0);
	(str[i] == '+' || str[i] == '-') ? i++ : (0);
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		j = res;
		res = res * 10 + (str[i] - '0');
		if (j > res)
			return (sign == 1 ? 0 : -1);
		i++;
	}
	if (sign == 1)
		return ((int)-res);
	else
		return ((int)res);
}
