/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BFS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 12:33:28 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/10 18:17:57 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	*BFS(int **matrix, t_info *info, int *prev, int *dist)
{
	t_queue	*queue;
	int		*visited;
	int		c;
	int		i;

	queue = NULL;
	i = -1;
	if (!(visited = (int *)malloc(sizeof(int) * info->room_nb)))
		return (NULL);
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
		while (++i <= info->room_nb)
		if (matrix[c][i] && !visited[i])
		{
			visited[i] = 1;
			dist[i] = dist[c] + 1;
			prev[i] = c;
			queue_add(&queue, i);
			if (i == info->room_nb - 1)
				return (1);
		}
	}
	return (0);
}