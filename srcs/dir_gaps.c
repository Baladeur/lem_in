/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_gaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:52:13 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/06 10:10:21 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	exit_bfs(t_queue **queue, int **visited, int **prev)
{
	if (queue && *queue)
		while (*queue)
			queue_delone(queue);
	if (visited && *visited)
	{
		free(*visited);
		*visited = NULL;
	}
	if (prev && *prev)
	{
		free(*prev);
		*prev = NULL;
	}
	return (NULL);
}

static int	bfs(int **matrix, t_info *info, int *dist)
{
	t_queue	*queue;
	int		*visited;
	int		*prev;
	int		c;
	int		i;

	visited = NULL;
	queue = NULL;
	prev = NULL;
	if (!(visited = (int *)malloc(sizeof(int) * info->room_nb))
		|| !(prev = (int *)malloc(sizeof(int) * info->room_nb))
		|| !(queue = queue_new(info->room_nb - 1)))
		return (exit_bfs(&queue, &visited, &prev));
	i = -1;
	while (++i < info->room_nb)
	{
		visited[i] = i == info->room_nb - 1 ? 1 : 0;
		dist[i] = i == info->room_nb - 1 ? 0 : INT32_MAX;
		prev[i] = -1;
	}
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
				if (!(queue_add(&queue, i)))
					return (exit_bfs(&queue, &visited, &prev));
			}
	}
}

static int	**exit_gaps(int ***directed, int **dist, t_info *info)
{
	if (directed && *directed)
		destroy_matrix(directed, info->room_nb);
	if (dist && *dist)
	{
		free(dist);
		*dist = NULL;
	}
	return (NULL);
}

int			**fill_gaps(int **matrix,int ***directed, t_info *info)
{
	int	*dist;
	int	x;
	int	y;

	if (!(dist = (int *)malloc(sizeof(int) * info->room_nb))
		|| !(bfs(matrix, info, dist)))
		return (exit_gaps(directed, &dist, info));
}
