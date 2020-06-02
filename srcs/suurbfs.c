/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurbfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 22:29:17 by tferrieu          #+#    #+#             */
/*   Updated: 2020/06/02 15:47:28 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	*suurbfs_exit(int **prev, t_queue **queue)
{
	if (prev && *prev)
		free(*prev);
	if (queue && *queue)
		while (*queue)
			queue_delone(queue);
	return (0);
}

int			*suurbfs(int **matrix, t_info *info)
{
	t_queue	*queue;
	int		*prev;
	int		i;

	if (!(prev = (int*)malloc(sizeof(int) * info->room_nb * 2 - 2)))
		return (0);
	i = -1;
	while (++i < info->room_nb * 2 - 2)
		prev[i] = -1;
	if (!(queue = queue_new(0)))
		return (suurbfs_exit(&prev, NULL));
	while (queue && (i = -1))
	{
		while (++i < info->room_nb * 2 - 2)
			if (matrix[queue->id][i] > 0 && prev[i] < 0)
			{
				if (!(queue_add(&queue, i)))
					return (suurbfs_exit(&prev, &queue));
				prev[i] = queue->id;
				if (i == info->room_nb * 2 - 3 && !(suurbfs_exit(NULL, &queue)))
					return (prev);
			}
		queue_delone(&queue);
	}
	return (suurbfs_exit(&prev, &queue));
}
