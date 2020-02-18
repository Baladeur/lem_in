/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 23:05:08 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/18 20:42:59 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int		is_better(t_path *src, t_path *dst, int ant_nb)
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

static void		pathtab_clone(t_path *src, t_path *dest, t_info *info)
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

static void		path_bt(t_path *paths, t_path *curr, t_path *best, t_info *info)
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

int			pathfinder(t_info *info, t_path *path_tab)
{
	t_path	*paths;
	t_path	*curr;
	int		max;
	int		i;

	paths = NULL;
	curr = NULL;
	path_tab = NULL;
	if (!(paths = allpath(info, &max))
		|| !(curr = pathtab_init(max, info))
		|| !(path_tab = pathtab_init(max, info)))
		return (pathfinder_exit(&paths, &curr, &path_tab));
	path_bt(paths, curr, path_tab, info);
	i = -1;
	while (path_tab[++i].len > 0 && (max = -1))
		while (paths[++max].len > 0)
			if (path_tab[i].edges == paths[i].edges && !(paths[i].edges = NULL))
				break ;
	pathfinder_exit(&paths, &curr, NULL);
	return (1);
}
