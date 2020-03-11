/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:58:49 by myener            #+#    #+#             */
/*   Updated: 2020/03/11 15:22:25 by tferrieu         ###   ########.fr       */
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

int			path_remove(t_path *path, t_info *info)
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
		return (1);
	while (++i < info->room_nb)
		prev[i] = -1;
	if (!(queue_add(&queue, 0)))
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
