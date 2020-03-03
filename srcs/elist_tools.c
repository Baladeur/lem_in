/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elist_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:07:41 by tferrieu          #+#    #+#             */
/*   Updated: 2020/03/03 16:42:15 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

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

t_elist	*elist_new(int *edges)
{
	t_elist *list;

	if (!(list = (t_elist *)malloc(sizeof(t_elist))))
		return (NULL);
	list->edges = edges;
	list->next = NULL;
	return (list);
}

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
