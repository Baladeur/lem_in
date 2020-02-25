/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:36:05 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/20 21:52:10 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Returns the number of instructions it would
** take for n ants to go through path.
*/

int		path_efficiency(t_path *path, int n)
{
	int longest;
	int remain;
	int i;

	i = 0;
	longest = path[0].len;
	while (path[++i].len > 0)
		if (path[i].len > longest)
			longest = path[i].len;
	remain = n;
	i = -1;
	while (path[++i].len > 0)
		remain -= longest - path[i].len;
	return (remain / i + longest - 1 + (remain % i ? 1 : 0));
}

/*
** Initialize a t_path tab of size 's'.
*/

t_path	*path_init(int s, t_info *info)
{
	t_path	*path;
	int		i;

	if (!(path = (t_path *)malloc(sizeof(t_path) * (s + 1))))
		return (NULL);
	i = -1;
	while (++i < s && !(path[i].edges = NULL))
		path[i].len = 0;
	path[s].len = -1;
	if (!(path[s].edges = (int *)malloc(sizeof(int) * info->room_nb)))
		return (path_free(&path, 0));
	i = -1;
	while (++i < info->room_nb)
		path[s].edges[i] = i == 0 || i == info->room_nb - 1 ? 1 : 0;
	return (path);
}

/*
** Adds a set of edges to a t_path tab. Returns 1 if the operation is
** successful, 0 if the set is incompatible with the other sets.
*/

int		path_add(t_path *path, int *edges, t_info *info, int b)
{
	int i;
	int s;
	int l;

	s = 0;
	while (path[s].len >= 0)
		s++;
	i = 0;
	l = 1;
	while (edges[++i] != info->room_nb - 1)
		if ((++l) && path[s].edges[edges[i]] && !b)
			return (0);
	i = -1;
	while (path[++i].len > 0)
		;
	path[i].len = l;
	path[i].edges = edges;
	i = 0;
	if (!b)
		while (edges[++i] != info->room_nb - 1)
			path[s].edges[edges[i]] = 1;
	return (1);
}

/*
** Removes the last set of edges from a t_path tab.
*/

int		path_remove(t_path *path, t_info *info)
{
	int i;
	int n;
	int s;

	s = 0;
	n = 0;
	while (path[s].len >= 0 && ++s)
		if (path[n + 1].len > 0)
			n++;
	if (!s || !path[n].len)
		return (0);
	i = 0;
	while (path[n].edges[++i] != info->room_nb - 1)
		path[s].edges[path[n].edges[i]] = 0;
	path[n].edges = NULL;
	path[n].len = 0;
	n = -1;
	while (path[++n].len > 0 && !(i = 0))
		while (path[n].edges[++i] != info->room_nb - 1)
			path[s].edges[path[n].edges[i]] = 1;
	return (1);
}
