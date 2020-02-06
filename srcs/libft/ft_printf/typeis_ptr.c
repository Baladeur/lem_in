/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeis_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:51:32 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:51 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		typeis_ptr(va_list ap, t_data *data)
{
	int		i;
	int		len;

	if (data->type->p)
	{
		data->type->p = va_arg(ap, long long int);
		len = (ft_hexlen(data->type->p) + 2);
		if ((data->lngt->width && (data->lngt->width_value > 0))
		&& !data->flag->minus && !data->flag->zero)
			widthprinter_nominus(data, len);
		ft_putstr("0x");
		i = 0;
		if (data->flag->zero)
			while (i++ < (data->lngt->width_value - len))
				ft_putchar('0');
		ft_putnbr_base(data->type->p, HEXL);
		if ((data->lngt->width && (data->lngt->width_value > 0))
			&& data->flag->minus)
			widthprinter_minus(data, len);
		return ((len < data->lngt->width_value) ? data->lngt->width_value
			: len);
	}
	return (-1);
}
