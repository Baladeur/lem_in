/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 12:33:28 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/20 16:44:53 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		BFS_exit(int **visited, t_queue **queue, int ret)
{
	if (visited && *visited)
	{
		free(*visited);
		*visited = NULL;
	}
	if (queue && *queue)
	{
		while (*queue)
			queue_delone(queue);
		*queue = NULL;
	}
	return (ret);
}

static t_path	*shortest_clean(t_path **shortest, int **prev, int **dist, int **edges)
{
	if (prev && *prev)
	{
		free(*prev);
		*prev = NULL;
	}
	if (dist && *dist)
	{
		free(*dist);
		*dist = NULL;
	}
	if (shortest && *shortest)
		destroy_path(shortest);
	return (NULL);
}

static int		BFS(int **matrix, t_info *info, int *prev, int *dist)
{
	t_queue	*queue;
	int		*visited;
	int		c;
	int		i;

	queue = NULL;
	visited = NULL;
	i = -1;
	if (!(visited = (int *)malloc(sizeof(int) * info->room_nb)))
		return (BFS_exit(&visited, &queue, 0));
	while (++i < info->room_nb)
	{
		visited[i] = i == 0 ? 1 : 0;
		dist[i] = i == 0 ? 0 : INT32_MAX;
		prev[i] = -1;
	}
	queue = queue_new(0);
	while (queue)
	{
		c = queue->id;
		queue_delone(&queue);
		i = -1;
		while (++i < info->room_nb)
			if (matrix[c][i] && !visited[i])
			{
				visited[i] = 1;
				dist[i] = dist[c] + 1;
				prev[i] = c;
				queue_add(&queue, i);
				if (i == info->room_nb - 1)
					return (BFS_exit(&visited, &queue,1));
			}
	}
	return (BFS_exit(&visited, &queue, 0));
}

static void		BFS_to_path(int *edges, int *prev, int pos, t_info *info)
{
	int cur;

	cur = info->room_nb - 1;
	while (pos >= 0 && cur >= 0)
	{
		edges[pos] = cur;
		cur = prev[cur];
		pos--;
	}
}

t_path			*shortest_path(int **matrix, t_info *info)
{
	t_path	*shortest;
	int		*edges;
	int		*prev;
	int		*dist;
	int		c;

	shortest = NULL;
	edges = NULL;
	prev = NULL;
	dist = NULL;
	c = 0;
	if (!(prev = (int *)malloc(sizeof(int) * info->room_nb)))
		return (NULL);
	if (!(dist = (int *)malloc(sizeof(int) * info->room_nb)))
		return (shortest_clean(&shortest, &prev, &dist, &edges));
	if (BFS(matrix, info, prev, dist) < 1)
		return (shortest_clean(&shortest, &prev, &dist, &edges));
	if (!(edges = (int *)malloc(sizeof(int) * (dist[info->room_nb - 1] + 1))))
		return (shortest_clean(&shortest, &prev, &dist, &edges));
	BFS_to_path(edges, prev, dist[info->room_nb - 1], info);
	if (!(shortest = new_path(edges, info->room_nb, dist[info->room_nb - 1] + 1)))
		return (shortest_clean(&shortest, &prev, &dist, &edges));
	shortest_clean(NULL, &prev, &dist, NULL);
	return (shortest);
}