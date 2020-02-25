/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:04:26 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/25 19:53:45 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	assign_path(t_path *path, t_info *info)
{
	int longest;
	int remain;
	int	split;
	int i[4];

	i[0] = 0;
	longest = path[0].len;
	while (path[++i[0]].len > 0)
		if (path[i[0]].len > longest)
			longest = path[i[0]].len;
	remain = info->ant_nb;
	i[0] = -1;
	while (path[++i[0]].len > 0)
		remain -= longest - path[i[0]].len;
	split = remain / i[0];
	remain = remain % i[0];
	i[1] = -1;
	i[2] = 0;
	while (path[++i[1]].len > 0 && (i[3] = -1))
		while (++i[3] < split + longest - path[i[1]].len
			+ (i[0] - i[1] <= remain ? 1 : 0))
		{
			info->ant[i[2]].path = path[i[1]].edges;
			i[2]++;
		}
}