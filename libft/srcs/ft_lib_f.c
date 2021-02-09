/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:54:50 by tyasmine          #+#    #+#             */
/*   Updated: 2019/11/23 19:56:53 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putchar_p(char c, t_f *str)
{
	write(1, &c, 1);
	str->iter++;
}

void	ft_putstr_p(char const *s, t_f *str)
{
	if (s)
	{
		while (*s)
			ft_putchar_p(*s++, str);
	}
}

char	*ft_itoa_base16(unsigned long long int value, int base, int f)
{
	char	*ret;
	char	*tab_base;
	int		taille;
	int		i;

	tab_base = f == 1 ? "0123456789abcdef" : "0123456789ABCDEF";
	if (value == 0)
		return ("0");
	taille = digit_count(value, base);
	if (!(ret = (char *)malloc(sizeof(char) * (taille + 1))))
		return (NULL);
	i = 1;
	while (value != 0)
	{
		ret[taille - i++] = tab_base[value % base];
		value /= base;
	}
	ret[taille] = '\0';
	return (ret);
}

char	*ft_itoa_base(long long int value, int base)
{
	char	*ret;
	char	*tab_base;
	int		taille;
	int		i;

	tab_base = "0123456789abcdef";
	if (value == 0)
		return ("0");
	taille = digit_count(value, base);
	if (!(ret = (char *)malloc(sizeof(char) * (taille + 1))))
		return (NULL);
	i = 1;
	while (value != 0)
	{
		ret[taille - i++] = tab_base[value % base];
		value /= base;
	}
	ret[taille] = '\0';
	return (ret);
}

void	ft_putnbr_p(long long int n, t_f *str)
{
	if (n == -9223372036854775807 - 1)
	{
		ft_putstr_p("-9223372036854775808", str);
	}
	else if (n < 0)
	{
		if (!(str->toch))
			ft_putchar_p('-', str);
		ft_putnbr_p(-n, str);
	}
	else if (n >= 10)
	{
		ft_putnbr_p(n / 10, str);
		ft_putchar_p(n % 10 + '0', str);
	}
	else if (n == 0 && str->t && str->toch == 0 && (!(str->f_sharp) ||
			str->f[str->i] == 'x' || str->f[str->i] == 'X'))
		n = 0;
	else
		ft_putchar_p(n + '0', str);
}
