/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:34:09 by mmarti            #+#    #+#             */
/*   Updated: 2019/10/22 16:34:11 by mmarti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char	*make_frac_str(long double num)
{
	unsigned char	*a;
	int				i;
	char			*str;
	int				j;
	int				k;

	i = 10;
	a = (unsigned char *)&num;
	if (!(str = (char *)malloc(10 * 8 + 1)))
		return (0);
	k = 0;
	while (--i >= 0)
	{
		j = 8;
		while (--j >= 0)
		{
			if (a[i] & (1 << j))
				str[k++] = '1';
			else
				str[k++] = '0';
		}
	}
	str[k] = 0;
	return (str);
}

int			get_exp(char *str)
{
	int i;
	int pow;
	int res;

	pow = 0;
	res = 0;
	i = 15;
	while (i > 0)
	{
		if (str[i] == '1')
			res += ft_pow2(pow);
		pow++;
		i--;
	}
	return (res);
}

int			dtoii(t_f *format, char *str)
{
	t_vars	vars;
	t_res	res;

	res.sign = 0;
	format->toch < 0 ? format->toch = 6 : 0;
	vars.entire = 0;
	vars.tmp = 16;
	*str == '1' ? res.sign = 1 : 0;
	vars.exp = get_exp(str) - 16383;
	if (vars.exp >= 0)
	{
		vars.entire = get_entire(&str[16], vars.exp);
		vars.tmp += vars.exp + 1;
		vars.exp = -1;
	}
	vars.frac = get_frac(&str[vars.tmp], vars.exp);
	res.num = ft_numjoin(vars.entire, vars.frac);
	res.entirelen = entlen(res.num);
	ft_round(res.num, format->toch);
	vars.ret = ft_putnum(res, format->toch, format);
	free(res.num);
	ft_free_vars(vars);
	return (vars.ret);
}

int			handle_num(t_f *format, char *str, int len)
{
	len += dtoii(format, str);
	free(str);
	return (len);
}

int			dtoi(long double a, t_f *format)
{
	char	*str;
	char	*res;
	int		len;

	len = 0;
	if (format->toch < 0)
		format->toch = 6;
	str = make_frac_str(a);
	if (!(res = check(str)))
		return (handle_num(format, str, len));
	len = 3;
	handle_fl_spec(format, *str - 48, &len);
	ft_putstr(res);
	if (format->shir > len)
		handle_w_spec(format, len);
	free(str);
	return (len + 3);
}
