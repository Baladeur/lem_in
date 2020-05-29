/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlap_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 22:24:21 by tferrieu          #+#    #+#             */
/*   Updated: 2020/05/29 22:12:57 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	add_edges(t_queue *queue, t_elist *edges)
{
	t_elist	*new;
	t_queue *pos;
	int		i;

	new = edges;
	if (new->edges)
	{
		while (new->next)
			new = new->next;
		if (!(new->next = (t_elist *)malloc(sizeof(t_elist))))
			return (0);
		new = new->next;
		new->next = NULL;
	}
	i = queue_size(queue) + 1;
	if (!(new->edges = (int *)malloc(sizeof(int) * i)))
		return (0);
	pos = queue;
	while (--i && pos)
	{
		new->edges[i] = pos->id;
		pos = pos->next;
	}
	new->edges[0] = 0;
	return (1);
}

static int	extract_rec(int **matrix, t_queue *prev, t_elist *edges, t_info *info)
{
	t_queue	*curr;
	int		i;

	if (prev->id == info->room_nb - 1)
		return (add_edges(prev, edges));
	if ((i = -1) && !(curr = queue_new(0)))
		return (0);
	curr->next = prev;
	while (++i < info->room_nb)
		if (matrix[prev->id][i] > 0 && (curr->id = i))
			if (!(extract_rec(matrix, curr, edges, info)))
				return (0);
	return (1);
}

t_elist	*extract_exit(t_elist **edges, t_queue **queue, t_info *info)
{
	int i;

	if (queue && *queue)
		queue_delone(queue);
	if (edges && *edges && (i = -1))
	{
		while (++i < info->path_nb)
			while ((*edges)[i].next)
				elist_delone(&((*edges)[i].next), 1);
		free(*edges);
		*edges = NULL;
	}
	return (NULL);
}

t_elist	*extract_edges(int **matrix, t_info *info)
{
	t_queue	*start;
	t_elist	*edges;
	int		pos;
	int		i;

	if (!(edges = (t_elist *)malloc(sizeof(t_elist) * info->path_nb)))
		return (NULL);
	i = -1;
	while (++i < info->path_nb && !(edges[i].next = NULL))
		edges[i].edges = NULL;
	if (!(start = queue_new(0)))
		return (extract_exit(&edges, NULL, info));
	i = 0;
	pos = -1;
	while (++i < info->room_nb)
	{
		if (matrix[0][i] && ++pos < info->path_nb && (start->id = i))
			if (!(extract_rec(matrix, start, &(edges[pos]), info)))
				return (extract_exit(&edges, &start, info));
	}
	extract_exit(NULL, &start, info);
	return (edges);
}

void		matrix_update(t_elist *path, int **matrix, t_info *info)
{
	t_elist	*curr;
	int		pos;
	int		src;
	int		dst;

	pos = -1;
	while (++pos < info->room_nb && (src = -1))
		while (++src < info->room_nb)
			matrix[pos][src] = 0;
	curr = path;
	while (curr && (pos = info->room_nb * 3 - 5))
	{
		while (pos)
		{
			dst = (pos + 2) / 3;
			src = (curr->edges[pos] + 2) / 3;
			matrix[src][dst] += 1;
			matrix[dst][src] -= 1;
			pos = curr->edges[pos];
		}
		curr = curr->next;
	}
}

int			pathmaker(t_elist *edges, t_path *new, int i, t_info *info)
{
	t_elist *current;
	
	if (new[i].len < 0)
		return (1);
	current = &(edges[i]);
	while (current)
	{
		if (path_add(new, current->edges, info, 0))
		{
			if (pathmaker(edges, new, i + 1, info))
				return (1);
			path_remove(new, info);
		}
		current = current->next;
	}
	return (0);
}

int			overlap_handler(t_elist *path, int **matrix, t_info *info, t_path **best)
{
	t_path	*new;
	t_elist	*edges;

	
	new = NULL;
	matrix_update(path, matrix, info);
	if (!(edges = extract_edges(matrix, info)))
		return (0);
	if (!(new = path_init(info->path_nb, info))
		|| !(pathmaker(edges, new, 0, info)))
		return ((extract_exit(&edges, NULL, info))? 0 : 0);
	if (!(*best) || path_efficiency(new, info->ant_nb)
		< path_efficiency(*best, info->ant_nb))
	{
		path_free(best, 1);
		*best = new;
	}
	else
		path_free(&new, 1);
	return (1);
}
