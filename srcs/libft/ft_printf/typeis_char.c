/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeis_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:51:42 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:35 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		typeis_char(va_list ap, t_data *data)
{
	int	ln;

	if (data->type->c)
	{
		data->spec->car = va_arg(ap, int);
		ln = 1;
		if ((data->lngt->width && (data->lngt->width_value > 0))
			&& !data->flag->minus)
			widthprinter_nominus(data, ln);
		ft_putchar(data->spec->car);
		if ((data->lngt->width && (data->lngt->width_value > 0))
			&& data->flag->minus)
			widthprinter_minus(data, ln);
		return ((ln < data->lngt->width_value) ? data->lngt->width_value : ln);
	}
	return (-1);
}
