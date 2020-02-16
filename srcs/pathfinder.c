/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:05:08 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/17 00:09:33 by tferrieu         ###   ########.fr       */
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

static void		pathtab_clone(t_path *src, t_path *dest, t_info *info)
{
	int i;
	int j;

	i = -1;
	while (src[++i].len >= 0 && (dest[i].len = src[i].len))
		dest[i].edges = src[i].edges;
	j = -1;
	while (++j < info->room_nb - 1)
		dest[i].edges[j] = src[i].edges[j];
}

static void		path(t_path *pathlist, t_path *curr, t_path *best, t_info *info)
{
	int	i;

	if (pathtab_efficiency(curr, info->ant_nb)
		< pathtab_efficiency(best, info->ant_nb))
		pathtab_clone(curr, best, info);
	if (pathlist[0].len < 0)
		return ;
	i = -1;
	while (pathlist[++i].len > 0)
	{
		if (pathtab_add(curr, pathlist[i].edges, info, 0))
		{
			path(pathlist + sizeof(t_path) * (i + 1), curr, best, info);
			pathtab_remove(curr, info);
		}
	}
	return ;
}

static t_path	*pathfinder_exit(t_path **paths, t_path **curr, t_path **best)
{
	if (paths && *paths)
		pathtab_destroy(paths, 1);
	if (curr && *curr)
		pathtab_destroy(curr, 0);
	if (best && *best)
		pathtab_destroy(best, 0);
	return (NULL);
}

t_path			*pathfinder(int **directed, t_info *info)
{
	t_path	*pathlist;
	t_path	*curr;
	t_path	*best;
	int		max;

	pathlist = NULL;
	curr = NULL;
	best = NULL;
	max = pathtab_max(directed, info);
	if (!(pathlist = allpath(directed, info))
		|| !(curr = pathtab_init(max, info))
		|| !(best = pathtab_init(max, info)))
		return (pathfinder_exit(&pathlist, &curr, &best));
	path(pathlist, curr, best, info);
	// ISOLATE THE BEST PATH FROM PATHLIST
	pathfinder_exit(&pathlist, &curr, NULL);
	return (best);
}
