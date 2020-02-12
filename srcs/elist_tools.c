/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elist_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:07:41 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/12 20:23:08 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Returns the current size of the edges list.
*/

int		elist_size(t_elist *list)
{
	t_elist	*current;
	int		n;

	n = 0;
	current = list;
	while (current)
	{
		n++;
		current = current->next;
	}
	return (n);
}

/*
** Returns the edges in the i element of the list.
** If the list is smaller than i, returns -1.
*/


int		*elist_get_at(t_elist *list, int i)
{
	t_elist *current;
	int		n;

	n = 0;
	current = list;
	while (current && n < i)
	{
		n++;
		current = current->next;
	}
	if (current)
		return (current->edges);
	else
		return (-1);
}

/*
** Initialize a chained list t_elist with it's first element edges.
*/


t_elist	*elist_new(int *edges)
{
	t_elist *list;

	if (!(list = (t_elist *)malloc(sizeof(t_elist))))
		return (NULL);
	list->edges = edges;
	list->next = NULL;
	return (list);
}

/*
** Removes and frees the first element of the list.
** if b != 0, also frees the edges stored in the element.
*/


void	elist_delone(t_elist **list, int b)
{
	t_elist *tmp;

	if (!list || !(*list))
		return ;
	tmp = (*list)->next;
	if ((*list)->edges && b)
		free((*list)->edges);
	free(*list);
	*list = tmp;
}

/*
** Add an element with the given edges at the bottom of the list.
*/


t_elist	*elist_add(t_elist **list, int *edges)
{
	t_queue *pos;

	if (!list)
		return (NULL);
	if (!*list)
		return (*list = elist_new(edges));
	pos = *list;
	while (pos->next)
		pos = pos->next;
	if (!(pos->next = elist_new(edges)))
		while (*edges)
			queue_delone(edges);
	return (*edges);
}