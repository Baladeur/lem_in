/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multi_BFS.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:14:12 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/21 16:56:44 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	multi_BFS_exit(t_queue **queue, int ret)
{
	if (queue && *queue)
	{
		while (*queue)
			queue_delone(queue);
		*queue = NULL;
	}
	return (ret);
}

int			multi_BFS(int **matrix, t_info *info, t_queue **prev, t_queue **dist)
{
	t_queue *queue;
	int		x;
	int		c;
	int		i;

	i = -1;
	queue = queue_new(0);
	x = matrix[0][0];
	matrix[0][0] = 0;
	while (queue)
	{
		c = queue->id;
		queue_delone(&queue);
		i = -1;
		while (++i < info->room_nb)
			if (matrix[c][i] && queue_size(dist[i]) < x && queue_size(prev[i]) < x && i)
			{
				queue_add(dist + i, dist[c]->id + 1);
				queue_add(prev + i, c);
				queue_add(&queue, i);
				if (i == info->room_nb -1 && queue_size(prev[i]) == x)
					return (multi_BFS_exit(&queue, 1));
			}
	}
	return (multi_BFS_exit(&queue, 0));
}
