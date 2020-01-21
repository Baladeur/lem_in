/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_shortest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:55:43 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/21 16:56:11 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_path	*x_shortest_clean(t_path **shortest, t_queue ***prev, t_queue ***dist, int **edges)
{
}

static t_queue	**init_queues(t_info *info, int first)
{
	t_queue **queues;
	int		i;

	i = 0;
	queues = NULL;
	if (!(queues = (t_queue **)malloc(sizeof(t_queue *) * info->room_nb)))
		return (NULL);
	while (++i < info->room_nb)
		queues[i] = NULL;
	if (!(queues[0] = queue_new(first)))
	{
		free(queues);
		return (NULL);
	}
	return (queues);
}

t_path			*x_shortest_path(int **matrix, t_info *info, int x)
{
	t_queue	**prev;
	t_queue	**dist;
	t_path	*shortest;
	int		*edges;
	int		c;

	shortest = NULL;
	edges = NULL;
	c = 0;
	if (!(prev = init_queues(info, -1)))
		return (x_shortest_clean(&shortest, &prev, &dist, &edges));
	if (!(dist = init_queues(info, 0)))
		return (x_shortest_clean(&shortest, &prev, &dist, &edges));
	matrix[0][0] = x;
	if (multi_BFS(matrix, info, prev, dist) < 1)
		return (x_shortest_clean(&shortest, &prev, &dist, &edges));
	if (!(edges = (int *)malloc(sizeof(int) * (queue_get_at(dist[info->room_nb - 1], x - 1) + 1))))
		return (x_shortest_clean(&shortest, &prev, &dist, &edges));
	BFS_to_path(edges, prev, dist[info->room_nb - 1], info);
	if (!(shortest = new_path(edges, info->room_nb, queue_get_at(dist[info->room_nb - 1], x - 1) + 1)))
		return (x_shortest_clean(&shortest, &prev, &dist, &edges));
	x_shortest_clean(NULL, &prev, &dist, NULL);
	return (shortest);
}