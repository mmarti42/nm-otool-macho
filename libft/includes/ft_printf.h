/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:08:18 by tyasmine          #+#    #+#             */
/*   Updated: 2019/11/23 19:45:34 by tyasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../includes/libft.h"
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <float.h>
# define LG2 0.301
# define LG5 0.7

typedef struct			s_form
{
	char				*f;
	int					i;
	int					f_min;
	int					f_plus;
	int					f_prob;
	int					f_sharp;
	int					f_null;
	int					shir;
	int					toch;
	int					dlin;
	va_list				ap;
	int					a;
	char				*s;
	int					t;
	long long int		p;
	unsigned long int	pp;
	char				*tmp;
	int					iter;
	int					her;
}						t_f;

typedef struct			s_pow
{
	char				*num;
	int					size;
	struct s_pow		*next;
}						t_pow;

typedef struct			s_res
{
	char				*num;
	int					entirelen;
	int					sign;
}						t_res;

typedef struct			s_vars
{
	int					ret;
	int					exp;
	int					tmp;
	t_pow				*entire;
	t_pow				*frac;
}						t_vars;

void					spec_format(t_f *str);
void					spec(t_f *str);
void					spec_d(t_f *str);
void					spec_u(t_f *str);
void					spec_u_o_x(t_f *str);
void					spec_u_u(t_f *str);
void					past_o(t_f *str);
void					past_oo(t_f *str);
void					past_ooo(t_f *str);
void					past_o_o(t_f *str);
void					past_x(t_f *str);
void					past_d(t_f *str);
void					past_dd(t_f *str);
void					past_ddd(t_f *str);
void					past_dc(t_f *str);
void					past_db(t_f *str);
void					past_da(t_f *str);
int						ft_nbr_len(long long int n);
void					ft_putnbr_p(long long int n, t_f *str);
void					spec_p(t_f *str);
void					spec_p_p(t_f *str);
char					*ft_itoa_base(long long int value, int base);
char					*ft_itoa_base16(unsigned long long int value,
		int base, int f);
size_t					digit_count(unsigned long nb, int base);
void					spec_cs(t_f *str);
void					pasts(t_f *str);
void					pastc(t_f *str);
void					spec_prc(t_f *str);
void					dlin(t_f *str);
void					dlin_plus(t_f *str, int x, int h, int l);
void					toch(t_f *str);
void					shir(t_f *str);
void					flag(t_f *str);
void					list_null(t_f *str);
void					ft_putstr_p(char const *s, t_f *str);
void					ft_putchar_p(char c, t_f *str);
long					ft_pow2(int pow);
int						ft_printf(char *format, ...);
int						dtoi(long double a, t_f *format);
t_pow					*get_entire(char *mantissa, int exp);
void					carry(char *num, int size);
void					tutu(char *num, int size, int pow);
t_pow					*division(char *num, int divider, int size);
t_pow					*get_frac(char *mantissa, int exp);
t_pow					*get_last(t_pow *lst);
int						ft_putnum(t_res res, int precision, t_f *format);
int						entlen(char *num);
char					*ft_numjoin(t_pow *entire, t_pow *frac);
char					*entirestr(t_pow *entire);
char					*fracstr(t_pow *frac);
void					*ft_ncpy(void *destination,
		const void *source, size_t n);
void					ft_round(char *num, int precision);
void					ft_free_pow(t_pow *lst);
void					ft_free_vars(t_vars vars);
int						ft_parse_float(va_list vaptr, t_f *list);
void					handle_fl_spec(t_f *format, char c, int *len);
void					handle_w_spec(t_f *format, int len);
char					*check(char *str);

#endif
