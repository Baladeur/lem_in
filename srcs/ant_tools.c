/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:04:26 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/20 18:34:37 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	assign_path(t_path *pathtab, t_info *info)
{
	int longest;
	int remain;
	int	split;
	int i[4];

	i[0] = 0;
	longest = pathtab[0].len;
	while (pathtab[++i[0]].len > 0)
		if (pathtab[i[0]].len > longest)
			longest = pathtab[i[0]].len;
	remain = info->ant_nb;
	i[0] = -1;
	while (pathtab[++i[0]].len > 0)
		remain -= longest - pathtab[i[0]].len;
	split = remain / i[0];
	remain = remain % i[0];
	i[1] = -1;
	i[2] = 0;
	while (pathtab[++i[1]].len > 0 && (i[3] = -1))
		while (++i[3] < split + longest - pathtab[i[1]].len
			+ (i[0] - i[1] <= remain ? 1 : 0))
		{
			info->ant[i[2]].path = pathtab[i[1]].edges;
			i[2]++;
		}
}