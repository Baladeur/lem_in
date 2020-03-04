/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:07:36 by tferrieu          #+#    #+#             */
/*   Updated: 2020/03/04 20:34:45 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Returns the theorical maximum simultaneous paths for a map given a directed
** graph.
*/

static int	path_max(int **directed, t_info *info)
{
	int c1;
	int c2;
	int i;

	c1 = 0;
	c2 = 0;
	i = -1;
	while (++i < info->room_nb)
	{
		if (directed[0][i])
			c1++;
		if (directed[info->room_nb - 1][i])
			c2++;
	}
	return (c1 > c2 ? c2 : c1);
}

/*
** Transforms a queue from the allpath DFS into an edge set to be added
** to the path list.
*/

static int	add_to_list(int pos, t_queue *parent, t_elist **list, int size)
{
	t_queue	*current;
	int		*edges;
	int		len;

	edges = NULL;
	len = queue_size(parent);
	if (!(edges = (int *)malloc(sizeof(int) * (len + 2))))
		return (0);
	current = parent;
	edges[len + 1] = size - 1;
	edges[len] = pos;
	while (--len > 0)
	{
		edges[len] = current->id;
		current = current->next;
	}
	edges[len] = 0;
	if (!elist_add(list, edges))
	{
		free(edges);
		return (0);
	}
	return (1);
}

/*
** DFS through the directed graph, adding every path it finds to the path list.
*/

static int	allpath_bt(t_queue *parent, int **dir, int pos, t_elist **list)
{
	t_queue	*current;
	int		i;
	int		b;

	if ((i = -1) && dir[pos][dir[0][0] - 1])
		return (add_to_list(pos, parent, list, dir[0][0]));
	b = 0;
	while (++i < dir[0][0])
		if (dir[pos][i] > 0 && pos != i && (b = 1))
			break ;
	if ((i = -1) && !b)
		return (1);
	if (!(current = queue_new(pos)))
		return (0);
	current->next = parent;
	while (++i < dir[0][0])
		if (dir[pos][i] > 0 && pos != i && (!parent || parent->id != i))
			if (!(allpath_bt(current, dir, i, list)))
				return (queue_delone(&current));
	queue_delone(&current);
	return (1);
}

/*
** Stores every possible path in a t_path tab.
*/

t_path		*allpath(t_info *info, int *max)
{
	t_elist	*list;
	t_path	*allpath;

	list = NULL;
	allpath = NULL;
	info->dir_matrix[0][0] = info->room_nb;
	*max = path_max(info->dir_matrix, info);
	if (!(allpath_bt(NULL, info->dir_matrix, 0, &list))
		|| !(allpath = path_init(elist_size(list), info)))
	{
		while (list)
			elist_delone(&list, 1);
		return (NULL);
	}
	info->dir_matrix[0][0] = 0;
	while (list && path_add(allpath, list->edges, info, 1))
		elist_delone(&list, 0);
	return (allpath);
}
