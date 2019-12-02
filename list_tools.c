/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:58:11 by myener            #+#    #+#             */
/*   Updated: 2019/12/02 16:11:27 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


t_room			*room_node_malloc(t_room *node)
{
	if (!(node = malloc(sizeof(t_room))))
		return (NULL);
	node->id = 0;
	node->name = NULL;
	node->x = 0;
	node->y = 0;
	node->type = 'c'; // default room type is classic
	node->ant_nb_curr = 0;
	node->matrix = NULL;
	node->next = NULL;
	return (node);
}

void			list_free(t_room *head)
{
	t_room	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
