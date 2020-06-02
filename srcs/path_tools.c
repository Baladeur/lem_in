/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:58:49 by myener            #+#    #+#             */
/*   Updated: 2020/06/02 18:31:45 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Returns the number of instructions it would
** take for n ants to go through path.
*/

int			path_efficiency(t_path *path, int n)
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
** Adds a set of edges to a t_path tab. Returns 1 if the operation is
** successful, 0 if the set is incompatible with the other sets.
*/

int			path_add(t_path *path, int *edges, t_info *info, int b)
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
	i = 0;
	while (path[i].len > 0)
		i++;
	path[i].len = l;
	path[i].edges = edges;
	i = 0;
	if (!b)
		while (edges[++i] != info->room_nb - 1)
			path[s].edges[edges[i]] = 1;
	return (1);
}

static int	path_exist_exit(t_queue **queue, int **prev)
{
	if (queue && *queue)
		while (*queue)
			queue_delone(queue);
	if (prev && *prev)
		free(*prev);
	return (0);
}

/*
** Check if start isn't connected to end.
*/

int			path_exist(t_info *info)
{
	t_queue	*queue;
	int		*prev;
	int		i;

	queue = NULL;
	i = -1;
	if (!(prev = (int *)malloc(sizeof(int) * info->room_nb)))
		return (0);
	while (++i < info->room_nb)
		prev[i] = -1;
	if (!(queue = queue_new(0)))
		return (path_exist_exit(&queue, &prev));
	while (queue && (i = 0) >= 0)
	{
		while (++i < info->room_nb)
			if (info->matrix[queue->id][i] && prev[i] < 0)
				if ((prev[i] = queue->id) >= 0 && !(queue_add(&queue, i)))
					return (path_exist_exit(&queue, &prev));
		queue_delone(&queue);
	}
	i = prev[info->room_nb - 1] >= 0 ? 1 : 0;
	free(prev);
	return (i);
}

/*
** Sets the path each ant will use once pathfinding is done.
*/

void		assign_path(t_path *path, t_info *info)
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
