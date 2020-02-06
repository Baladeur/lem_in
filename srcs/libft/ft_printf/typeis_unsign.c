/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeis_unsign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:53:22 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:56 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static long long	converter(t_data *data)
{
	long long int nb;

	nb = 0;
	if (data->size->h)
		nb = ((unsigned short int)data->type->u);
	else if (data->size->hh)
		nb = ((unsigned char)data->type->u);
	else if (data->size->l)
		nb = ((unsigned long int)data->type->u);
	else if (data->size->ll)
		nb = ((unsigned long long int)data->type->u);
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
	return (len);
}

static int			writer(t_data *data, int len, int prec_len)
{
	t_lngt *lngt;

	lngt = data->lngt;
	if ((lngt->width && (lngt->width_value > 0)) && !data->flag->minus)
		widthprinter_nominus(data, len);
	if (lngt->prec)
		precision_printer(data, prec_len);
	if (data->type->u != 0 || (data->type->u == 0 && !lngt->prec_zero
		&& !lngt->prec_rien))
		ft_putunbr_long(data->type->u);
	if ((lngt->width && (lngt->width_value > 0)) && data->flag->minus)
		widthprinter_minus(data, len);
	if (lngt->prec_value > lngt->width_value)
		lngt->width_value += lngt->prec_value;
	return ((len < lngt->width_value) ? lngt->width_value : len);
}

int					typeis_unsign(va_list ap, t_data *data, t_lngt *lngt)
{
	int	len;
	int	prec_len;

	if (data->type->u)
	{
		data->type->u = va_arg(ap, unsigned long long int);
		data->type->u = (data->tool->size ? converter(data) :
			((unsigned int)data->type->u));
		len = ft_uintlen(data->type->u);
		len = ((data->type->u == 0) && (lngt->prec_zero || lngt->prec_rien)) ?
			0 : len;
		len = troubleshooter(data, len);
		prec_len = (lngt->prec && !lngt->prec_rien && !lngt->prec_zero) ?
			ft_uintlen(data->type->u) : 0;
		if (((data->lngt->prec_zero || data->lngt->prec_rien)
			&& data->type->u > 0) || data->type->u || data->type->u == 0)
			return (writer(data, len, prec_len));
		return (data->lngt->width_value);
	}
	return (-1);
}
