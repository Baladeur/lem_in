/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:05:08 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/18 23:52:44 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Compare src with dest. Returns 1 if src is better, 0 otherwise.
*/

static int	is_better(t_path *src, t_path *dst, int ant_nb)
{
	int i;
	int l1;
	int l2;

	if (pathtab_efficiency(src, ant_nb) > pathtab_efficiency(dst, ant_nb))
		return (0);
	if (pathtab_efficiency(src, ant_nb) < pathtab_efficiency(dst, ant_nb))
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

/*
** Duplicates src pathtab values into dest pathtab values.
*/

static void	pathtab_clone(t_path *src, t_path *dest, t_info *info)
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

/*
** Backtracking algorithm testing every path combination to find the best one.
*/

static void	path_bt(t_path *paths, t_path *curr, t_path *best, t_info *info)
{
	int	i;

	if (curr[0].len && (!best[0].len || is_better(curr, best, info->ant_nb)))
		pathtab_clone(curr, best, info);
	if (paths[0].len < 0)
		return ;
	i = -1;
	while (paths[++i].len > 0)
	{
		if (pathtab_add(curr, paths[i].edges, info, 0))
		{
			path_bt(&(paths[i + 1]), curr, best, info);
			pathtab_remove(curr, info);
		}
	}
	return ;
}

/*
** Destroys the pathfinder's allocated variables in case of failure.
*/

static int	pathfinder_exit(t_path **paths, t_path **curr, t_path **best)
{
	if (paths && *paths)
		pathtab_destroy(paths, 1);
	if (curr && *curr)
		pathtab_destroy(curr, 0);
	if (best && *best)
		pathtab_destroy(best, 0);
	return (0);
}

/*
** Returns the best combination of paths given a specified map.
*/

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
		|| !(curr = pathtab_init(max, info))
		|| !(*best = pathtab_init(max, info)))
		return (pathfinder_exit(&paths, &curr, best));
	path_bt(paths, curr, *best, info);
	i = -1;
	while (best[0][++i].len > 0 && (max = -1))
		while (paths[++max].len > 0)
			if (best[0][i].edges == paths[i].edges && !(paths[i].edges = NULL))
				break ;
	pathfinder_exit(&paths, &curr, NULL);
	return (1);
}
