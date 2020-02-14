/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:07:36 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/13 17:07:36 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	add_to_list(int pos, t_queue *parent, t_elist **list, int size)
{
	t_queue	*current;
	int 	*edges;
	int		len;

	*edges = NULL;
	len = queue_size(parent);
	if (!(edges = (int *)malloc(sizeof(int) * (len + 2))))
		return (0);
	current = parent;
	edges[len + 1] = size - 1;
	edges[len] = pos;
	while (--len >=0)
	{
		edges[len] = current->id;
		current = current->next;
	}
	if (!elist_add(list, edges))
	{
		free(edges);
		return (0);
	}
	return (1);
}

static int	allpath_bt(t_queue *parent, int **dir, int pos, t_elist **list)
{
	t_queue	*current;
	int		res;
	int		i;
	int		b;

	if (dir[pos][dir[0][0]])
		return (add_to_list(pos, parent, list, dir[0][0]));
	i = -1;
	b = 0;
	while (++i < dir[0][0])
		if (dir[pos][i] > 0 && pos != i && (b = 1))
			break;
	if ((i = -1) && !b)
		return (1);
	if (!(current = queue_new(pos)))
		return (0);
	while (++i < dir[0][0])
		if (dir[pos][i] > 0 && pos != i)
			if (!(allpath_bt(current, dir, i, list)))
			{
				queue_delone(&current);
				return (0);
			}
	queue_delone(&current);
	return (1);
}

t_path		*allpath(int **directed, t_info *info)
{
	t_elist	*list;

	list = NULL;
	directed[0][0] = info->room_nb;
	if (!(allpath_bt(NULL, directed, 0, list)))
	{
		while (list)
			elist_delone(&list, 1);
		return (NULL);
	}
	return (list);
}
