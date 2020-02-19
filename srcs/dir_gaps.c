/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_gaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:52:13 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/19 17:17:13 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Destroys BFS' allocated variables in case of a failure running the algorithm.
*/

static int	exit_loop(t_queue **queue, int **prev, int ret)
{
	if (queue && *queue)
		while (*queue)
			queue_delone(queue);
	if (prev && *prev)
	{
		free(*prev);
		*prev = NULL;
	}
	return (ret);
}

/*
** The loop used during the BFS.
*/

static int	bfs_loop(int *visited, int *dist, t_info *info)
{
	t_queue	*queue;
	int		*prev;
	int		i;
	int		c;

	queue = NULL;
	prev = NULL;
	if (!(prev = (int *)malloc(sizeof(int) * info->room_nb))
		|| !(queue = queue_new(info->room_nb - 1)))
		return (exit_loop(&queue, &prev, 0));
	i = -1;
	while (++i < info->room_nb)
		prev[i] = -1;
	while (queue && (c = queue->id) >= 0)
	{
		queue_delone(&queue);
		i = 0;
		while (++i < info->room_nb)
			if (info->matrix[c][i] && !visited[i] && (visited[i] = 1)
				&& (dist[i] = dist[c] + 1)
				&& (prev[i] = c))
				if (!(queue_add(&queue, i)))
					return (exit_loop(&queue, &prev, 0));
	}
	return (exit_loop(&queue, &prev, 1));
}

/*
** BFS through the adjacency matrix to determine distance between each room and
** the end.
*/

static int	bfs(t_info *info, int *dist)
{
	int		*visited;
	int		i;

	visited = NULL;
	if (!(visited = (int *)malloc(sizeof(int) * info->room_nb)))
		return (0);
	i = -1;
	while (++i < info->room_nb)
	{
		visited[i] = i == info->room_nb - 1 ? 1 : 0;
		dist[i] = i == info->room_nb - 1 ? 0 : INT32_MAX;
	}
	if (!(bfs_loop(visited, dist, info)))
	{
		free(visited);
		return (0);
	}
	free(visited);
	return (1);
}

/*
** Destroys the directed matrix in case of a failure while filling gaps.
*/

static int	exit_gaps(int **dist, t_info *info)
{
	if (info->dir_matrix)
		matrix_free(&(info->dir_matrix), info->room_nb);
	if (dist && *dist)
	{
		free(dist);
		*dist = NULL;
	}
	return (0);
}

/*
** Performs a double check on the directed graph and fills the remaining gaps.
*/

int			fill_gaps(t_info *info)
{
	int	*dist;
	int	x;
	int	y;

	if (!(dist = (int *)malloc(sizeof(int) * info->room_nb))
		|| !(bfs(info, dist)))
		return (exit_gaps(&dist, info));
	y = -1;
	while (++y < info->room_nb)
	{
		x = -1;
		while (++x < info->room_nb)
			if (info->matrix[y][x] && !info->dir_matrix[y][x])
			{
				if (dist[y] < dist[x] && (info->dir_matrix[y][x] = -1))
					info->dir_matrix[x][y] = 1;
				else if (dist[x] < dist[y] && (info->dir_matrix[x][y] = -1))
					info->dir_matrix[y][x] = 1;
				else if (dist[x] == dist[y] && (info->dir_matrix[x][y] = 1))
					info->dir_matrix[y][x] = 1;
			}
	}
	free(dist);
	return (1);
}
