/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:12:36 by myener            #+#    #+#             */
/*   Updated: 2019/10/23 15:53:27 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void		parse_width(char *instruc, t_data *data, int i)
{
	int		j;
	char	*width_value;

	width_value = ft_strnew(ft_strlen(instruc) - 1);
	data->lngt->width = 1;
	if (i > 0 && instruc[i - 1] == '.')
		return ;
	j = 0;
	while ((instruc[i] >= '0' && instruc[i] <= '9') && instruc[i])
	{
		width_value[j] = instruc[i];
		i++;
		j++;
	}
	data->lngt->width_value = ft_atoi(width_value);
	data->tool->index = i;
	free(width_value);
}

void		parse_prec(char *instruc, t_lngt *lngt, t_tool *tool, int i)
{
	int		j;
	int		start;
	char	*stk;

	i++;
	j = 0;
	start = i;
	stk = ft_strnew(ft_strlen(instruc) - 1);
	lngt->prec = 1;
	while (instruc[i] >= '0' && instruc[i] <= '9')
	{
		stk[j] = instruc[i];
		i++;
		j++;
	}
	lngt->prec_value = ft_atoi(stk);
	if (instruc[start] == '0' && !lngt->prec_value)
		lngt->prec_zero = 1;
	if (!lngt->prec_zero && !lngt->prec_value)
		lngt->prec_rien = 1;
	tool->index2 = i;
}
