/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 18:18:29 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/26 17:45:00 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Returns the current size of the queue.
*/

int		queue_size(t_queue *queue)
{
	t_queue	*current;
	int		n;

	n = 0;
	current = queue;
	while (current)
	{
		n++;
		current = current->next;
	}
	return (n);
}

/*
** Returns the value stored in the i element of the queue.
** If the list is smaller than i, returns -1.
*/

int		queue_get_at(t_queue *queue, int i)
{
	t_queue *current;
	int		n;

	n = 0;
	current = queue;
	while (current && n < i)
	{
		n++;
		current = current->next;
	}
	if (current)
		return (current->id);
	else
		return (-1);
}

/*
** Initialize a chained list t_queue with it's first element id.
*/

t_queue	*queue_new(int id)
{
	t_queue *queue;

	if (!(queue = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	queue->id = id;
	queue->next = NULL;
	return (queue);
}

/*
** Removes and frees the first element of the queue.
*/

int		queue_delone(t_queue **queue)
{
	t_queue *tmp;

	if (!queue || !(*queue))
		return (0);
	tmp = (*queue)->next;
	free(*queue);
	*queue = tmp;
	return (0);
}

/*
** Add an element with the given id at the bottom of the queue.
*/

t_queue	*queue_add(t_queue **queue, int id)
{
	t_queue *pos;

	if (!queue)
		return (NULL);
	if (!*queue)
		return (*queue = queue_new(id));
	pos = *queue;
	while (pos->next)
		pos = pos->next;
	if (!(pos->next = queue_new(id)))
		while (*queue)
			queue_delone(queue);
	return (*queue);
}
