/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeis_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:51:38 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:54 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		troubleshooter(t_data *data, int len)
{
	t_lngt *lngt;

	lngt = data->lngt;
	lngt->width = (lngt->prec && (lngt->width_value <= lngt->prec_value)) ?
		0 : lngt->width;
	lngt->prec = (lngt->prec && (lngt->prec_value >= len)) ? 0 : lngt->prec;
	if (lngt->prec && !lngt->prec_rien && !lngt->prec_zero)
		len = lngt->prec_value;
	return (len);
}

static void		errormanager(t_data *data, int len, char *err)
{
	t_lngt *lngt;

	lngt = data->lngt;
	if (data->tool->str_tp == NULL)
	{
		len = 6;
		if ((lngt->width && (lngt->width_value > 0)) && !data->flag->minus)
			widthprinter_nominus(data, len);
		if (!data->lngt->prec_zero && !data->lngt->prec_rien)
			ft_putstr("(null)");
		if ((lngt->width && (lngt->width_value > 0)) && data->flag->minus)
			widthprinter_minus(data, len);
	}
	else if (ft_strcmp(data->tool->str_tp, err) == 0)
	{
		len = 0;
		if ((data->lngt->width && (data->lngt->width_value > 0)))
			widthprinter_nominus(data, len);
	}
}

static int		writer(t_data *data, t_lngt *lngt, int len, int p_ln)
{
	int		i;

	if ((lngt->width && (lngt->width_value > 0)) && !data->flag->minus)
		widthprinter_nominus(data, len);
	if ((!lngt->prec_zero && !lngt->prec_rien) || lngt->prec)
	{
		if (lngt->prec && (lngt->prec_value <= p_ln && (lngt->prec_value > 1)))
		{
			i = -1;
			while (i++ < (lngt->prec_value - 1))
				ft_putchar(data->tool->str_tp[i]);
			len = (lngt->prec_value <= len) ? lngt->prec_value : len;
		}
		else if (!lngt->prec || ((lngt->prec && lngt->prec_value > p_ln)))
			ft_putstr(data->tool->str_tp);
	}
	if ((lngt->width && (lngt->width_value > 0)) && data->flag->minus)
		widthprinter_minus(data, len);
	if (lngt->prec_value > lngt->width_value)
		lngt->width_value += lngt->prec_value;
	return ((len < lngt->width_value) ? lngt->width_value : len);
}

int				typeis_str(va_list ap, t_data *data)
{
	int		len;
	int		prec_len;
	t_lngt	*lngt;
	t_tool	*tool;

	lngt = data->lngt;
	tool = data->tool;
	if (tool->str_tp || data->type->s)
	{
		len = 0;
		tool->str_tp = va_arg(ap, char*);
		if (tool->str_tp == NULL || ft_strcmp(tool->str_tp, "") == 0)
		{
			errormanager(data, len, "");
			return ((len < lngt->width_value) ? lngt->width_value : len);
		}
		len = ft_strlen(tool->str_tp);
		len = troubleshooter(data, len);
		prec_len = (lngt->prec && !lngt->prec_rien && !lngt->prec_zero) ?
			ft_strlen(tool->str_tp) : 0;
		if (((lngt->prec_zero || lngt->prec_rien) && prec_len > 0) || len)
			return (writer(data, lngt, len, prec_len));
		return (lngt->width_value);
	}
	return (-1);
}
