/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:21:05 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:31 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void		widthprinter_minus(t_data *data, int len)
{
	int i;

	i = -1;
	data->lngt->width_value--;
	while (i++ < (data->lngt->width_value - len))
		ft_putchar(' ');
	data->lngt->width_value++;
}

void		widthprinter_nominus(t_data *data, int len)
{
	int i;

	len += 1;
	i = (data->spec->flt ? 0 : -1);
	if (data->flag->zero)
		while (i++ < (data->lngt->width_value - len))
			ft_putchar('0');
	else if (!data->flag->zero)
		while (i++ < (data->lngt->width_value - len))
			ft_putchar(' ');
	len -= 1;
}

void		precision_printer(t_data *data, int len)
{
	int	i;

	i = 0;
	while (i++ < (data->lngt->prec_value - len))
		ft_putchar('0');
}
