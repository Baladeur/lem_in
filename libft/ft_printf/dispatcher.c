/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:56:58 by myener            #+#    #+#             */
/*   Updated: 2019/04/04 16:51:13 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		dispatcher(va_list ap, t_data *data)
{
	if (data->type->d || data->type->i)
		data->tool->ret = typeis_int(ap, data, data->lngt);
	else if (data->type->c)
		data->tool->ret = typeis_char(ap, data);
	else if (data->type->s)
		data->tool->ret = typeis_str(ap, data);
	else if (data->type->p)
		data->tool->ret = typeis_ptr(ap, data);
	else if (data->type->o)
		data->tool->ret = typeis_octal(ap, data, data->lngt);
	else if (data->type->u)
		data->tool->ret = typeis_unsign(ap, data, data->lngt);
	else if (data->type->x)
		data->tool->ret = typeis_hexl(ap, data, data->lngt);
	else if (data->type->big_x)
		data->tool->ret = typeis_hexu(ap, data, data->lngt);
	else if (data->type->f)
		data->tool->ret = typeis_float(ap, data);
	else if (data->tool->perc)
		data->tool->ret = typeis_perc(data, data->lngt);
}
