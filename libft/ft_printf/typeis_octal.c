/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeis_octal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:59:01 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:47 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static long long	converter(t_data *data)
{
	long long int nb;

	nb = 0;
	if (data->size->h)
		nb = ((unsigned short int)data->type->o);
	else if (data->size->hh)
		nb = ((unsigned char)data->type->o);
	else if (data->size->l)
		nb = ((unsigned long int)data->type->o);
	else if (data->size->ll)
		nb = ((unsigned long long int)data->type->o);
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
	if (data->flag->sharp && data->type->o != 0 && !data->lngt->prec)
		len += 1;
	return (len);
}

static void			intern(t_data *data, t_lngt *lngt, int len, int p_ln)
{
	if ((lngt->width && (lngt->width_value > 0)) && !data->flag->minus)
		widthprinter_nominus(data, len);
	if (data->flag->sharp && (data->type->o == 0) && (lngt->prec_zero ||
		lngt->prec_rien)
		&& lngt->width)
		ft_putchar('0');
	if (lngt->prec)
		precision_printer(data, p_ln);
	if (data->type->o != 0 || (data->type->o == 0 && !lngt->prec_zero &&
	!lngt->prec_rien))
		ft_putunbr_base(data->type->o, OCT);
	if ((lngt->width && (lngt->width_value > 0)) && data->flag->minus)
		widthprinter_minus(data, len);
}

static int			writer(t_data *data, int len, int prec_len)
{
	t_lngt	*lngt;
	t_flag	*flag;
	t_type	*type;

	lngt = data->lngt;
	flag = data->flag;
	type = data->type;
	if ((flag->sharp && (type->o != 0) && !lngt->prec) || (flag->sharp &&
	(type->o == 0) && (lngt->prec_zero || lngt->prec_rien) && !lngt->width))
	{
		ft_putchar('0');
		len += ((flag->sharp && (type->o == 0) && (lngt->prec_zero ||
		lngt->prec_rien) && !lngt->width)) ? 1 : 0;
	}
	if (flag->sharp && (data->type->o == 0) && (lngt->prec_zero
		|| lngt->prec_rien) && lngt->width)
		len++;
	intern(data, lngt, len, prec_len);
	if (lngt->prec_value > lngt->width_value)
		lngt->width_value += lngt->prec_value;
	return ((len < lngt->width_value) ? lngt->width_value : len);
}

int					typeis_octal(va_list ap, t_data *data, t_lngt *lngt)
{
	int len;
	int	prec_len;

	if (data->type->o)
	{
		data->type->o = va_arg(ap, unsigned long long int);
		data->type->o = (data->tool->size ? converter(data) :
			((unsigned int)data->type->o));
		len = ft_octlen(data->type->o);
		len = ((data->type->o == 0) && (lngt->prec_zero || lngt->prec_rien))
			? 0 : len;
		len = troubleshooter(data, len);
		prec_len = (lngt->prec && !lngt->prec_rien && !lngt->prec_zero) ?
			ft_octlen(data->type->o) : 0;
		if (((data->lngt->prec_zero || data->lngt->prec_rien)
			&& data->type->o > 0) || ((lngt->prec_zero || lngt->prec_rien)
			&& data->lngt->width) || data->type->o || data->type->o == 0)
			return (writer(data, len, prec_len));
		return (data->lngt->width_value);
	}
	return (-1);
}
