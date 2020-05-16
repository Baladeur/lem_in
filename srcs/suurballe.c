/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 18:26:17 by tferrieu          #+#    #+#             */
/*   Updated: 2020/05/16 23:38:17 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int	**adj_split(t_info *info)
{
	int	**new;
	int i;
	int j;

	new = NULL;
	if (!(new = init_matrix(info->room_nb * 3 - 4)))
		return (NULL);
	j = -1;
	while (++j < info->room_nb && (i = -1))
		while (++i < info->room_nb)
			if (info->matrix[j][i])
			{
				new[j > 1 ? j * 3 - 2 : j][i > 1 ? i * 3 - 2 : i] = 1;
				new[i > 1 ? i * 3 - 2 : i][j > 1 ? j * 3 - 2 : j] = 1;
			}
	return (new);
}

int	*suurbfs_exit(int **prev, t_queue **queue)
{
	if (prev && *prev)
		free(*prev);
	if (queue && *queue)
		while (*queue)
			queue_delone(queue);
	return (0);
}

int	*suurbfs(int **matrix, t_info *info)
{
	t_queue	*queue;
	int		*prev;
	int		i;

	if (!(prev = (int*)malloc(sizeof(int) * info->room_nb * 3 - 4)))
		return (0);
	i = -1;
	while (++i < info->room_nb * 3 - 4)
		prev[i] = -1;
	if (!(queue = queue_new(0)))
		return (suurbfs_exit(&prev, NULL));
	while (queue && (i = -1))
	{
		while (++i < info->room_nb * 3 - 4)
			if (matrix[queue->id][i] > 0 && prev[i] < 0)
			{
				if (!(queue_add(&queue, i)))
					return (suurbfs_exit(&prev, &queue));
				prev[i] = queue->id;
				if (i == info->room_nb * 3 - 5 && !(suurbfs_exit(NULL, &queue)))
					return (prev);
			}
		queue_delone(&queue);
	}
	return (suurbfs_exit(&prev, &queue));
}

int	suurballe_exit(int ***matrix, t_elist **paths, t_info *info)
{
	if (matrix && *matrix)
		matrix_free(matrix, info->room_nb * 3 - 4);
	if (paths && *paths)
		while (*paths)
			elist_delone(paths, 1);
	return (0);
}

void	split_node(int **matrix, int node, int *curr, t_info *info)
{
	int next;
	int i;

	i = info->room_nb * 3 - 5;
	while ((i = curr[i]))
		if (curr[i] == node && (next = curr[i]))
			break;
	i = -1;
	while (++i < info->room_nb * 3 - 4)
	{
		if (matrix[node][i] && i != next && i != curr[node])
		{
			matrix[node + 1][i] = -1;
			matrix[node + 2][i] = 1;
			matrix[i][node + 1] = 1;
			matrix[i][node + 2] = -1;
			matrix[node + 1][node + 2] = -1;
			matrix[node + 2][node + 1] = 1;
		}
		if (matrix[node][i])
		{
			matrix[node][i] = 0;
			matrix[i][node] = 0;
		}
	}
}

void	extend_path(int **matrix, int *curr, t_info *info)
{
	int pos;
	int src;
	int dst;

	pos = info->room_nb * 3 - 5;
	while ((pos = curr[pos]))
		if (!((pos - 1) % 3))
			split_node(matrix, pos, curr, info);
	pos = info->room_nb * 3 - 5;
	matrix[pos][(curr[pos] - 1) % 3 ? curr[pos] : curr[pos] + 2] = 1;
	matrix[(curr[pos] - 1) % 3 ? curr[pos] : curr[pos] + 2][pos] = -1;
	while ((pos = curr[pos]))
	{
		dst = (curr[pos] - 1) % 3 ? curr[pos] : curr[pos] + 2;
		src = (pos - 1) % 3 ? pos : pos + 1;
		matrix[src][dst] = 1;
		matrix[dst][src] = -1;
	}
	matrix[0][(pos - 1) % 3 ? pos : pos + 1] = -1;
	matrix[(pos - 1) % 3 ? pos : pos + 1][0] = 1;
}

int	add_to_paths(t_queue *pos, t_path *best, t_info *info)
{
	t_queue	*curr;
	int		*edges;
	int		len;

	edges = NULL;
	len = queue_size(pos);
	if (!(edges = (int *)malloc(sizeof(int) * len)))
		return (0);
	curr = pos;
	while (--len >= 0)
	{
		edges[len] = curr->id;
		curr = curr->next;
	}
	if (!(path_add(best, edges, info, 0)))
	{
		free(edges);
		return (0);
	}
	return (1);
}

int	extract_rec(int **matrix, t_queue *pos, t_info *info, t_path *best)
{
	t_queue	*current;

	if (pos->id == info->room_nb - 1)
		return (add_to_paths(pos, best, info));
	if (!(current = queue_new(-1)))
		return (0);
	current->next = pos;
	while (++current->id < info->room_nb)
		if (matrix[pos->id][current->id] > 0)
			if (!(extract_rec(matrix, current, info, best)))
				return (queue_delone(&current));
	queue_delone(&current);
	return (1);
}

int extract_exit(int ***matrix, t_queue **queue, t_path **best, t_info *info)
{
	if (matrix && *matrix)
		matrix_free(matrix, info->room_nb);
	if (queue && *queue)
		queue_delone(queue);
	if (best && *best)
		path_free(best, 1);
	return (0);
}

int	extract_paths(int ***matrix, t_info *info, t_path **best)
{
	t_queue *start;

	if (!(start = queue_new(0)))
		return (extract_exit(matrix, NULL, NULL, info));
	if (!(*best = path_init(info->path_nb, info)))
		return (extract_exit(matrix, NULL, NULL, info));
	if (!(extract_rec(*matrix, start, info, *best)))
		return (extract_exit(matrix, &start, best, info));
	queue_delone(&start);
	matrix_free(matrix, info->room_nb);
	return(1);
}

int	overlap_handler(t_elist *paths, t_info *info, t_path **best)
{
	t_elist	*curr;
	int		**squished;
	int		pos;
	int		src;
	int		dst;

	if (!(squished = init_matrix(info->room_nb)))
		return (0);
	curr = paths;
	while (curr && (pos = info->room_nb * 3 - 5))
	{
		while (pos)
		{
			dst = (pos + 2) / 3;
			src = (curr->edges[pos] + 2) / 3;
			squished[src][dst] += 1; 
			squished[dst][src] -= 1;
			pos = curr->edges[pos];
		}
		curr = curr->next;
	}
	return (extract_paths(&squished, info, best));
}

int	suurballe(t_info *info, t_path **best)
{
	t_elist	*paths;
	int		**matrix;
	int		*curr;

	paths = NULL;
	curr = NULL;
	if (!(matrix = adj_split(info)))
		return (0);
	while ((curr = suurbfs(matrix, info)))
	{
		if (!(elist_add(&paths, curr)))
			return (suurballe_exit(&matrix, &paths, info));
		extend_path(matrix, curr, info);
		info->path_nb++;
	}
	if (!(overlap_handler(paths, info, best)))
		return (suurballe_exit(&matrix, &paths, info));
	suurballe_exit(&matrix, &paths, info);
	return (1); // et non 0 :)
}
