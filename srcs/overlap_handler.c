/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlap_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 22:24:21 by tferrieu          #+#    #+#             */
/*   Updated: 2020/06/02 17:41:09 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	add_to_paths(t_queue *pos, t_path *best, t_info *info)
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

static int	extract_rec(int **matrix, t_queue *pos, t_info *info, t_path *best)
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

static int	extract_exit(t_queue **queue, t_path **best)
{
	if (queue && *queue)
		queue_delone(queue);
	if (best && *best)
		path_free(best, 1);
	return (0);
}

static int	extract_paths(int **matrix, t_info *info, t_path **best)
{
	t_queue *start;
	t_path	*new;

	if (!(start = queue_new(0)))
		return (0);
	if (!(new = path_init(info->path_nb, info)))
		return (extract_exit(&start, NULL));
	if (!(extract_rec(matrix, start, info, new)))
		return (extract_exit(&start, &new));
	if (!(*best) || path_efficiency(new, info->ant_nb)
		< path_efficiency(*best, info->ant_nb))
	{
		path_free(best, 1);
		*best = new;
	}
	else
		path_free(&new, 1);
	queue_delone(&start);
	return (1);
}

int			overlap_handler(t_elist *path, int **r, t_info *info, t_path **best)
{
	t_elist	*curr;
	int		pos;
	int		src;
	int		dst;

	pos = -1;
	while (++pos < info->room_nb && (src = -1))
		while (++src < info->room_nb)
			r[pos][src] = 0;
	curr = path;
	while (curr && (pos = info->room_nb * 2 - 3))
	{
		while (pos)
		{
			dst = (pos + 1) / 2;
			src = (curr->edges[pos] + 1) / 2;
			r[src][dst] += 1;
			r[dst][src] -= 1;
			pos = curr->edges[pos];
		}
		curr = curr->next;
	}
	return (extract_paths(r, info, best));
}
