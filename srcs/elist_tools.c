/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elist_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:07:41 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/17 22:16:00 by tferrieu         ###   ########.fr       */
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
	t_elist *pos;

	if (!list)
		return (NULL);
	if (!*list)
		return (*list = elist_new(edges));
	pos = *list;
	while (pos->next)
		pos = pos->next;
	if (!(pos->next = elist_new(edges)))
		return (NULL);
	return (*list);
}
