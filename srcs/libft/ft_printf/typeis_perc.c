/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeis_perc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:57:23 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:50 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		typeis_perc(t_data *data, t_lngt *lngt)
{
	int	len;

	if (data->tool->perc)
	{
		len = 1;
		if (lngt->prec && ((lngt->prec_value <= len) ||
			(lngt->prec_value >= lngt->width_value)))
			lngt->prec = 0;
		if ((lngt->width && (lngt->width_value <= len)) || ((lngt->prec &&
			lngt->width) && (lngt->width_value < lngt->prec_value)))
			lngt->width = 0;
		if ((lngt->prec_zero || lngt->prec_rien) || data->tool->perc)
		{
			if ((lngt->width && (lngt->width_value > 0)) && !data->flag->minus)
				widthprinter_nominus(data, len);
			ft_putchar('%');
			if ((lngt->width && (lngt->width_value > 0)) && data->flag->minus)
				widthprinter_minus(data, len);
			return ((len < lngt->width_value) ? lngt->width_value : len);
		}
		return (lngt->width_value);
	}
	return (-1);
}
