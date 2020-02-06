/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbenard <lbenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 10:32:38 by myener            #+#    #+#             */
/*   Updated: 2019/10/22 17:24:48 by lbenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>

# define OCT "01234567"
# define DECI "0123456789"
# define HEXL "0123456789abcdef"
# define HEXU "0123456789ABCDEF"
# define UINT_MAX 4294967296
# define INT_MAX 2147483647

typedef struct			s_spec
{
	int					integer;
	int					str;
	long double			flt;
	char				car;
	unsigned int		unint;
	signed char			signcar;
	short				sh;
	long				lg;
	long long			lglg;
}						t_spec;

typedef struct			s_flag
{
	int					minus;
	int					plus;
	int					zero;
	int					space;
	int					sharp;
}						t_flag;

typedef struct			s_lngt
{
	int					width;
	int					width_value;
	int					prec;
	int					prec_value;
	int					prec_zero;
	int					prec_rien;

}						t_lngt;

typedef struct			s_size
{
	int					h;
	int					hh;
	int					l;
	int					ll;
	int					big_l;
}						t_size;

typedef struct			s_type
{
	int							c;
	int							s;
	long long int				p;
	long long int				d;
	long long int				i;
	unsigned long long int		o;
	unsigned long long int		u;
	unsigned long long int		x;
	unsigned long long int		big_x;
	int							f;
}						t_type;

typedef struct			s_tool
{
	int						dioux;
	int						size;
	int						unsign;
	char					*str_tp;
	int						vir;
	unsigned long long int	flt_tmp;
	int						ret;
	int						neg;
	double					stock;
	int						flt_len;
	char					*flt_str;
	int						perc;
	int						index;
	int						index2;
}						t_tool;

typedef struct			s_data
{
	t_spec				*spec;
	t_flag				*flag;
	t_lngt				*lngt;
	t_size				*size;
	t_type				*type;
	t_tool				*tool;
}						t_data;

int						infnan(t_data *data, double num, int len);
void					cleaner(t_data *data);
void					endwriter(t_data *data, int zero, int prec_len,
						char *str);
void					finalizer(t_data *data);
void					free_malloc(t_data *data);
int						ft_printf(const char *format, ...);
void					ghostwriter(t_data *data, int len,
						unsigned long long int num);
void					overthedot(t_data *data, int p_ln);
void					parse_prec(char *instruc, t_lngt *lngt, t_tool *tool,
						int i);
void					parse_width(char *instruc, t_data *data, int i);
void					parser(char *instruc, t_data *data);
void					precision_printer(t_data *data, int len);
void					troublehelper(t_data *data, t_flag	*flag,
						t_spec *spec);
void					struct_malloc(t_data *data);
void					dispatcher(va_list ap, t_data *data);
int						typeis_int(va_list ap, t_data *data, t_lngt *lngt);
int						typeis_perc(t_data *data, t_lngt *lngt);
int						typeis_str(va_list ap, t_data *data);
int						typeis_ptr(va_list ap, t_data *data);
int						typeis_char(va_list ap, t_data *data);
int						typeis_unsign(va_list ap, t_data *data, t_lngt *lngt);
int						typeis_octal(va_list ap, t_data *data, t_lngt *lngt);
int						typeis_hexl(va_list ap, t_data *data, t_lngt *lngt);
int						typeis_hexu(va_list ap, t_data *data, t_lngt *lngt);
int						typeis_float(va_list ap, t_data *data);
void					widthprinter_minus(t_data *data, int len);
void					widthprinter_nominus(t_data *data, int len);

#endif
