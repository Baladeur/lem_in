/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeis_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:14:29 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:37 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include "libft.h"

static void	troubleshooter(t_data *data, int p_ln, int ln)
{
	t_lngt	*lngt;
	t_flag	*flag;
	t_spec	*spec;

	spec = data->spec;
	lngt = data->lngt;
	flag = data->flag;
	p_ln = (lngt->prec && !lngt->prec_rien && !lngt->prec_zero) ?
	lngt->prec_value : p_ln;
	lngt->prec = (lngt->prec && (lngt->prec_value <= p_ln)) ? 0 : lngt->prec;
	lngt->width = (lngt->width && ((lngt->width_value <= ln + p_ln) ||
		((lngt->prec && (lngt->width_value <= ln + p_ln))))) ?
		0 : lngt->width;
	troublehelper(data, flag, spec);
	ln += data->tool->vir + p_ln;
	if ((lngt->width && (lngt->width_value > 0)) && !flag->minus
		&& (lngt->width_value > (ln + 1)))
		widthprinter_nominus(data, ln);
	if (lngt->prec_zero)
		return ;
	spec->flt = (spec->flt < 0) ? -spec->flt : spec->flt;
}

static void	writer(t_data *data, int prec_len, char *str, long long int num)
{
	int						zero;
	unsigned long long int	tmp;
	int						len;

	zero = (((int)ft_strlen(str)) < prec_len);
	tmp = data->tool->flt_tmp;
	len = ((num < 0) ? ft_intlen(num) + 1 : ft_intlen(num));
	data->tool->vir = !data->tool->vir ? 1 : data->tool->vir;
	data->tool->vir += ((data->lngt->prec_rien || data->lngt->prec_zero) ?
		(prec_len - 1) : prec_len);
	data->tool->vir -= (!data->lngt->prec_rien && !data->lngt->prec_zero) ?
		1 : 0;
	ghostwriter(data, len, num);
	if (str[prec_len - 1] >= '5')
	{
		tmp = (ft_atoll(str)) + 1;
		str = ft_lltoa(tmp);
	}
	prec_len -= 1;
	endwriter(data, zero, prec_len, str);
}

int			float_helper(t_data *data, int p_ln, char *str, long long int num)
{
	t_lngt	*lngt;
	t_tool	*tool;

	lngt = data->lngt;
	tool = data->tool;
	if (((lngt->prec_zero || lngt->prec_rien) && data->spec->flt != 0) ||
	data->spec->flt || data->spec->flt == 0)
	{
		writer(data, p_ln, str, num);
		tool->flt_len = (ft_intlen(num) + data->tool->vir);
		if (lngt->width && lngt->width_value && data->flag->minus)
			widthprinter_minus(data, tool->flt_len);
		return ((tool->flt_len < lngt->width_value) ? lngt->width_value
			: tool->flt_len);
	}
	return (lngt->width_value);
}

int			typeis_float(va_list ap, t_data *data)
{
	int				p_ln;
	long long int	num;
	t_lngt			*lngt;

	lngt = data->lngt;
	if (data->type->f)
	{
		p_ln = (lngt->prec ? (lngt->prec_value + 1) : 7);
		p_ln = ((lngt->prec_zero || lngt->prec_rien) ? 0 : p_ln);
		data->spec->flt = va_arg(ap, double);
		data->tool->stock = data->spec->flt;
		num = data->spec->flt;
		data->tool->flt_len = ft_intlen(num);
		if (infnan(data, data->spec->flt, data->tool->flt_len))
			return (0);
		troubleshooter(data, p_ln, data->tool->flt_len);
		if (data->spec->flt < 0)
			data->spec->flt = -data->spec->flt;
		data->tool->neg = (num < 0) ? 1 : 0;
		num = (num < 0) ? -num : num;
		data->spec->flt -= num;
		overthedot(data, p_ln);
		return (float_helper(data, p_ln, data->tool->flt_str, num));
	}
	return (-1);
}
