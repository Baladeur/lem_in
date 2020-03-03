/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:04:26 by tferrieu          #+#    #+#             */
/*   Updated: 2020/03/03 16:44:00 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	assign_path(t_path *path, t_info *info)
{
	int l;
	int r;
	int	s;
	int i[4];

	i[0] = 0;
	l = path[0].len;
	while (path[++i[0]].len > 0)
		if (path[i[0]].len > l)
			l = path[i[0]].len;
	r = info->ant_nb;
	i[0] = -1;
	while (path[++i[0]].len > 0)
		r -= l - path[i[0]].len;
	s = r / i[0];
	r = r % i[0];
	i[1] = -1;
	i[2] = 0;
	while (path[++i[1]].len > 0 && (i[3] = -1))
		while (++i[3] < s + l - path[i[1]].len + (i[0] - i[1] <= r ? 1 : 0))
		{
			info->ant[i[2]].path = path[i[1]].edges;
			i[2]++;
		}
}
