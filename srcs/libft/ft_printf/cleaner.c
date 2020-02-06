/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:48:05 by myener            #+#    #+#             */
/*   Updated: 2019/04/08 21:08:23 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		cleaner_helper(t_data *data)
{
	data->type->f = 0;
	data->spec->integer = 0;
	data->spec->str = 0;
	data->spec->car = 0;
	data->spec->flt = 0;
	data->spec->unint = 0;
	data->spec->signcar = 0;
	data->spec->sh = 0;
	data->spec->lg = 0;
	data->spec->lglg = 0;
	data->tool->perc = 0;
	data->tool->size = 0;
	data->tool->unsign = 0;
	data->tool->index = 0;
	data->tool->index2 = 0;
	data->tool->ret = 0;
	data->tool->flt_tmp = 0;
	data->tool->vir = 0;
	data->tool->neg = 0;
	data->tool->flt_len = 0;
	data->tool->flt_str = NULL;
	data->tool->str_tp = NULL;
}

void			cleaner(t_data *data)
{
	data->flag->minus = 0;
	data->flag->plus = 0;
	data->flag->zero = 0;
	data->flag->space = 0;
	data->flag->sharp = 0;
	data->lngt->width = 0;
	data->lngt->width_value = 0;
	data->lngt->prec = 0;
	data->lngt->prec_value = 0;
	data->lngt->prec_zero = 0;
	data->lngt->prec_rien = 0;
	data->size->h = 0;
	data->size->ll = 0;
	data->size->l = 0;
	data->size->hh = 0;
	data->type->c = 0;
	data->type->s = 0;
	data->type->p = 0;
	data->type->d = 0;
	data->type->i = 0;
	data->type->o = 0;
	data->type->u = 0;
	data->type->x = 0;
	data->type->big_x = 0;
	cleaner_helper(data);
}

void			struct_malloc(t_data *data)
{
	if (!(data->spec = malloc(sizeof(t_spec))))
		return ;
	if (!(data->flag = malloc(sizeof(t_flag))))
		return ;
	if (!(data->lngt = malloc(sizeof(t_lngt))))
		return ;
	if (!(data->size = malloc(sizeof(t_size))))
		return ;
	if (!(data->type = malloc(sizeof(t_type))))
		return ;
	if (!(data->tool = malloc(sizeof(t_tool))))
		return ;
}

void			free_malloc(t_data *data)
{
	if (data->spec)
		free(data->spec);
	if (data->flag)
		free(data->flag);
	if (data->lngt)
		free(data->lngt);
	if (data->size)
		free(data->size);
	if (data->type)
		free(data->type);
	if (data->tool)
	{
		if (data->tool->flt_str)
			free(data->tool->flt_str);
		free(data->tool);
	}
}
