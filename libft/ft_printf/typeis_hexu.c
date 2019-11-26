/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeis_hexu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:06:08 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:42 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static long long	convert(t_data *data)
{
	long long int nb;

	nb = 0;
	if (data->size->h)
		nb = ((unsigned short int)data->type->big_x);
	else if (data->size->hh)
		nb = ((unsigned char)data->type->big_x);
	else if (data->size->l)
		nb = ((unsigned long int)data->type->big_x);
	else if (data->size->ll)
		nb = ((unsigned long long int)data->type->big_x);
	return (nb);
}

static int			troubleshooter(t_data *data, int len)
{
	t_lngt *lngt;

	lngt = data->lngt;
	lngt->width = (lngt->width && ((lngt->width_value <= len) ||
		((lngt->prec && (lngt->width_value <= lngt->prec_value))))) ?
		0 : lngt->width;
	lngt->prec = (lngt->prec && (lngt->prec_value <= len)) ? 0 : lngt->prec;
	if (lngt->prec && !lngt->prec_rien && !lngt->prec_zero)
		len = lngt->prec_value;
	if (data->flag->sharp && data->type->big_x != 0)
		len += 2;
	return (len);
}

static int			writer(t_data *data, int len, int prec_len)
{
	t_lngt *lngt;
	t_flag *flag;

	lngt = data->lngt;
	flag = data->flag;
	if (flag->sharp && data->type->big_x != 0)
		ft_putstr("0X");
	if ((lngt->width && (lngt->width_value > 0)) && !flag->minus)
		widthprinter_nominus(data, len);
	if (lngt->prec)
		precision_printer(data, prec_len);
	if (data->type->big_x != 0 || (data->type->big_x == 0 &&
		!lngt->prec_zero && !lngt->prec_rien))
		ft_putunbr_base(data->type->big_x, HEXU);
	if ((lngt->width && (lngt->width_value > 0)) && flag->minus)
		widthprinter_minus(data, len);
	if (lngt->prec_value > lngt->width_value)
		lngt->width_value += lngt->prec_value;
	return ((len < lngt->width_value) ? lngt->width_value : len);
}

int					typeis_hexu(va_list ap, t_data *data, t_lngt *lngt)
{
	int		len;
	int		prec_len;
	t_type	*type;
	t_tool	*tool;

	len = 0;
	prec_len = 0;
	tool = data->tool;
	type = data->type;
	if (type->big_x)
	{
		type->big_x = va_arg(ap, unsigned long long int);
		type->big_x = tool->size ? convert(data) : ((unsigned int)type->big_x);
		len = ft_hexlen(type->big_x);
		len = ((type->big_x == 0) && (lngt->prec_zero || lngt->prec_rien)) ?
			0 : len;
		len = troubleshooter(data, len);
		prec_len = (lngt->prec && !lngt->prec_rien && !lngt->prec_zero) ?
			ft_hexlen(type->big_x) : 0;
		if (((lngt->prec_zero || lngt->prec_rien) && (type->big_x > 0)) ||
		((lngt->prec_zero || lngt->prec_rien) && lngt->width) || type->big_x)
			return (writer(data, len, prec_len));
		return (lngt->width_value);
	}
	return (-1);
}
