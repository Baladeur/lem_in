/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rounder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:20:14 by myener            #+#    #+#             */
/*   Updated: 2019/04/25 17:19:30 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	roundit_awayzero(float f)
{
	int	nb;

	nb = f;
	return ((float)(nb + 1));
}

float	roundit_towardzero(float f)
{
	int	nb;

	nb = f;
	return ((float)nb);
}

float	roundit_halfeven(float f)
{
	float r;
	float d;

	r = (roundit_awayzero(f));
	d = f - ((int)f);
	if (ft_floatmod(r, 2.0f) == 0.0f)
		return (r);
	return (f - d);
}
