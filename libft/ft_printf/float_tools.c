/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:34:39 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:21 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		infnan(t_data *data, double num, int len)
{
	t_lngt *lngt;
	t_flag *flag;

	lngt = data->lngt;
	flag = data->flag;
	if ((num != num) || (num >= 1 / 0.0 && num <= 1 / 0.0)
		|| (num >= -1 / 0.0 && num <= -1 / 0.0))
	{
		len += flag->minus ? 2 : 1;
		len += (num >= -1 / 0.0 && num <= -1 / 0.0) ? 1 : 0;
		if ((lngt->width && (lngt->width_value > 0)) && !flag->minus
			&& (lngt->width_value > (len + 1)))
			widthprinter_nominus(data, len);
		if (num != num)
			ft_putstr("nan");
		else if (num >= 1 / 0.0 && num <= 1 / 0.0)
			ft_putstr("inf");
		else if (num >= -1 / 0.0 && num <= -1 / 0.0)
			ft_putstr("-inf");
		if (lngt->width && lngt->width_value && flag->minus)
			widthprinter_minus(data, len);
		return (1);
	}
	return (0);
}

void	ghostwriter(t_data *data, int len, unsigned long long int num)
{
	char	*stk;

	stk = ft_strnew(len);
	stk = ft_lltoa(num);
	if (((data->lngt->prec_rien || data->lngt->prec_zero)) &&
		((stk[len - 1] >= '5') || num == 0))
	{
		if ((num != 0) && (stk[len - 1] > '5'))
			num = ft_atoll(stk) + 1;
		num -= (!data->tool->neg && num != 0 && (stk[len - 1] > '5')) ? 1 : 0;
		ft_putnbr_long(num);
		if (data->flag->sharp)
			ft_putchar('.');
		data->tool->vir += (data->flag->sharp ? 1 : 0);
	}
	else if ((!data->lngt->prec_rien && !data->lngt->prec_zero && num == 0)
		|| num != 0)
	{
		ft_putnbr_long(num);
		if ((!data->lngt->prec_rien && !data->lngt->prec_zero)
			|| data->flag->sharp)
			ft_putchar('.');
	}
	free(stk);
}

void	endwriter(t_data *data, int zero, int prec_len, char *str)
{
	t_lngt	*lngt;
	int		i;

	lngt = data->lngt;
	lngt->prec_value = prec_len;
	i = -1;
	if (!zero)
		while (i++ < (prec_len - 1))
			ft_putchar(str[i]);
	else if (zero)
		precision_printer(data, (((int)ft_strlen(str))));
}

void	troublehelper(t_data *data, t_flag *flag, t_spec *spec)
{
	if (spec->flt < 0)
	{
		ft_putchar('-');
		data->tool->vir++;
	}
	else if (flag->plus || flag->space)
	{
		if (flag->plus)
			ft_putchar('+');
		else if (flag->space)
			ft_putchar(' ');
		data->tool->vir++;
	}
	if (flag->sharp && (!flag->zero || (flag->sharp && (spec->flt == 0)
		&& flag->zero)))
		data->tool->vir++;
}

void	overthedot(t_data *data, int p_ln)
{
	int						i;
	unsigned long long int	tmp;

	i = 0;
	tmp = 0;
	data->tool->flt_str = ft_strnew(p_ln);
	ft_bzero(data->tool->flt_str, p_ln);
	while (data->spec->flt && i < p_ln)
	{
		data->spec->flt *= 10;
		tmp = data->spec->flt;
		data->tool->flt_str[i] = ft_itoc(tmp);
		data->spec->flt -= tmp;
		i++;
	}
	data->tool->flt_tmp = tmp;
}
