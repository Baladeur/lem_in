/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeis_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:51:47 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:44 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static long long	converter(t_data *data, long long int nb)
{
	if (data->size->h)
		nb = ((short)nb);
	else if (data->size->hh)
		nb = ((char)nb);
	else if (data->size->l)
		nb = ((long)nb);
	return (nb);
}

static int			troubleshooter(t_lngt *lngt, int len)
{
	lngt->prec = (lngt->prec && (lngt->prec_value <= len)) ? 0 : lngt->prec;
	lngt->width = (lngt->width && ((lngt->width_value <= len) ||
		((lngt->prec && (lngt->width_value <= lngt->prec_value))))) ?
		0 : lngt->width;
	if (lngt->prec && !lngt->prec_rien && !lngt->prec_zero)
		len = lngt->prec_value;
	return (len);
}

static int			writer(t_data *data, long long int nb, int len, int prec)
{
	t_lngt *lngt;
	t_flag *flag;

	lngt = data->lngt;
	flag = data->flag;
	if (!flag->zero && (lngt->width && (lngt->width_value > 0)) && !flag->minus)
		widthprinter_nominus(data, len);
	if (nb < 0)
		ft_putchar('-');
	else if (flag->plus && (nb >= 0))
		ft_putchar('+');
	if (data->flag->space && !data->flag->plus && !lngt->width && (nb >= 0))
		ft_putchar(' ');
	if (flag->zero && (lngt->width && (lngt->width_value > 0) && !flag->minus))
		widthprinter_nominus(data, len);
	if (lngt->prec)
		precision_printer(data, prec);
	if (nb != 0 || (nb == 0 && !lngt->prec_zero && !lngt->prec_rien))
		ft_putnbr_long(nb);
	if ((lngt->width && (lngt->width_value > 0)) && flag->minus)
		widthprinter_minus(data, len);
	if (lngt->prec_value > lngt->width_value)
		lngt->width_value += lngt->prec_value;
	return ((len < lngt->width_value) ? lngt->width_value : len);
}

int					typeis_int(va_list ap, t_data *data, t_lngt *lngt)
{
	long long int	nb;
	int				len;
	int				prec_len;

	if (data->type->d || data->type->i)
	{
		nb = va_arg(ap, long long int);
		nb = (data->tool->size ? converter(data, nb) : ((int)nb));
		len = ft_intlen(nb);
		len = ((nb == 0) && (lngt->prec_zero || lngt->prec_rien)) ? 0 : len;
		len = troubleshooter(lngt, len);
		prec_len = (lngt->prec && !lngt->prec_rien && !lngt->prec_zero) ?
			ft_intlen(nb) : 0;
		if (nb < 0)
			len++;
		if (data->flag->plus && ((nb > 0 && data->flag->zero) || nb >= 0))
			len++;
		data->flag->space = (data->flag->space && (nb >= 0));
		if (data->flag->space && !lngt->width)
			len++;
		if (((lngt->prec_zero || lngt->prec_rien) && nb > 0) || nb == 0 || nb)
			return (writer(data, nb, len, prec_len));
		return (lngt->width_value);
	}
	return (-1);
}
