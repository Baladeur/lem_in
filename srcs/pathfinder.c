/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:05:08 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/12 21:36:08 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int		pathtab_max(int **directed, t_info *info)
{
	int c1;
	int c2;
	int i;

	c1 = 0;
	c2 = 0;
	i = -1;
	while (++i < info->room_nb)
	{
		if (directed[0][i])
			c1++;
		if (directed[info->room_nb - 1][i])
			c2++;
	}
	return (c1 > c2 ? c2 : c1);
}

static int		allpath_bt(t_queue *parent, int **dir, int pos, t_elist **list)
{
	t_queue	*current;
	int		res;
	int		i;
	int		b;

	i = -1;
	b = 0;
	while (++i < dir[0][0])
		if (dir[pos][i] && pos != i && (b = 1))
			break;
	if (!b)
		return (0);
	if (!(current = (t_queue *)malloc(sizeof(t_queue))))
		return (-1);
}

static t_elist	*allpath(int **directed, t_info *info)
{}

t_path			*pathfinder(int **directed, t_info *info)
{
}
