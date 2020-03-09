/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:05:08 by tferrieu          #+#    #+#             */
/*   Updated: 2020/03/09 12:17:47 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	is_better(t_path *src, t_path *dst, int ant_nb)
{
	int i;
	int l1;
	int l2;

	if (path_efficiency(src, ant_nb) > path_efficiency(dst, ant_nb))
		return (0);
	if (path_efficiency(src, ant_nb) < path_efficiency(dst, ant_nb))
		return (1);
	l1 = 0;
	l2 = 0;
	i = -1;
	while (src[++i].len > 0)
		l1 += src[i].len;
	i = -1;
	while (dst[++i].len > 0)
		l2 += dst[i].len;
	return (l1 < l2);
}

static void	path_clone(t_path *src, t_path *dest, t_info *info)
{
	int i;
	int j;

	i = -1;
	while (src[++i].len >= 0 && (dest[i].len = src[i].len) >= 0)
		dest[i].edges = src[i].edges;
	j = -1;
	while (++j < info->room_nb - 1)
		dest[i].edges[j] = src[i].edges[j];
}

static void	pathfind_bt(t_path *paths, t_path *curr, t_path *best, t_info *info)
{
	int	i;

	i = -1;
	if (curr[0].len && (!best[0].len || is_better(curr, best, info->ant_nb)))
		path_clone(curr, best, info);
	if (paths[0].len < 0)
		return ;
	i = -1;
	while (paths[++i].len > 0)
	{
		if (path_add(curr, paths[i].edges, info, 0))
		{
			pathfind_bt(&(paths[i + 1]), curr, best, info);
			path_remove(curr, info);
		}
	}
}

static int	pathfinder_exit(t_path **paths, t_path **curr, t_path **best)
{
	if (paths && *paths)
		path_free(paths, 1);
	if (curr && *curr)
		path_free(curr, 0);
	if (best && *best)
		path_free(best, 0);
	return (0);
}

int			pathfinder(t_info *info, t_path **best)
{
	t_path	*paths;
	t_path	*curr;
	int		max;
	int		i;

	paths = NULL;
	curr = NULL;
	*best = NULL;
	if (!(paths = allpath(info, &max))
		|| !(curr = path_init(max, info))
		|| !(*best = path_init(max, info)))
		return (pathfinder_exit(&paths, &curr, best));
	pathfind_bt(paths, curr, *best, info);
	i = -1;
	while (best[0][++i].len > 0 && (max = -1))
		while (paths[++max].len > 0)
			if (best[0][i].edges == paths[max].edges)
				paths[max].edges = NULL;
	info->path_nb = i;
	pathfinder_exit(&paths, &curr, NULL);
	return (1);
}
