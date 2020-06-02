/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 18:26:17 by tferrieu          #+#    #+#             */
/*   Updated: 2020/06/02 18:39:42 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	**adj_split(t_info *info)
{
	int	**matrix;
	int	x;
	int	y;

	if (!(matrix = init_matrix(info->room_nb * 2 - 2)))
		return (0);
	y = -1;
	while ((x = -1) && ++y < info->room_nb)
		while (++x < info->room_nb)
			if (info->matrix[y][x] && x && y != info->room_nb - 1)
				matrix[y * 2][x * 2 - 1] = 1;
	x = 0;
	while (++x < info->room_nb - 1)
		matrix[x * 2 - 1][x * 2] = 1;
	return (matrix);
}

static int	*suurbfs_exit(int **prev, t_queue **queue)
{
	if (prev && *prev)
		free(*prev);
	if (queue && *queue)
		while (*queue)
			queue_delone(queue);
	return (0);
}

static int	*suurbfs(int **matrix, t_info *info)
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

static int	suur_exit(int ***matrix, int ***map, t_elist **edges, t_info *info)
{
	if (matrix && *matrix)
		matrix_free(matrix, info->room_nb * 2 - 2);
	if (map && *map)
		matrix_free(map, info->room_nb);
	if (edges && *edges)
		while (*edges)
			elist_delone(edges, 1);
	return (0);
}

int			suurballe(t_info *info, t_path **best)
{
	t_elist	*edges;
	int		**matrix;
	int		**map;
	int		*curr;
	int		pos;

	edges = NULL;
	if (!(matrix = adj_split(info)))
		return (0);
	if (!(map = init_matrix(info->room_nb)))
		return (suur_exit(&matrix, NULL, NULL, info));
	while ((curr = suurbfs(matrix, info)) && ++info->path_nb)
	{
		if ((pos = info->room_nb * 2 - 3) && (!(elist_add(&edges, curr))
			|| !(overlap_handler(edges, map, info, best))))
			return (suur_exit(&matrix, &map, &edges, info));
		while (pos)
		{
			matrix[pos][curr[pos]] = 1;
			matrix[curr[pos]][pos] = 0;
			pos = curr[pos];
		}
	}
	suur_exit(&matrix, &map, &edges, info);
	return (1);
}
