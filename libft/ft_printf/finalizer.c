/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:51:23 by myener            #+#    #+#             */
/*   Updated: 2019/04/04 13:00:38 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	finalizer(t_data *data)
{
	data->tool->dioux = (data->type->d || data->type->i || data->type->o
	|| data->type->u || data->type->x || data->type->big_x);
	data->tool->unsign = (data->type->u || (data->type->o && (data->size->h
	|| data->size->hh || data->size->l || data->size->ll)) || (data->type->x
	&& (data->size->h || data->size->hh || data->size->l || data->size->ll))
	|| (data->type->big_x && (data->size->h || data->size->hh || data->size->l
	|| data->size->ll)));
	data->spec->integer = (data->type->d || data->type->i);
	data->flag->plus = (data->flag->plus && (data->spec->integer
	|| data->type->f));
	data->flag->space = (data->flag->space && !data->flag->plus);
	data->flag->zero = (data->flag->zero && !data->flag->minus);
	if ((data->flag->zero && data->lngt->prec) && data->tool->dioux)
		data->flag->zero = 0;
	data->flag->space = (data->flag->space && (data->type->d
	|| data->type->i || data->type->f));
	data->flag->sharp = (data->flag->sharp && (data->type->o || data->type->x
	|| data->type->big_x || data->type->f));
}
