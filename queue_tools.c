/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 18:18:29 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/19 19:12:08 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int		queue_get_at(t_queue *queue, int id)
{
	t_queue *current;
	int		n;

	n = 0;
	current = queue;
	while (current && n < id)
	{
		n++;
		current = current->next;
	}
	if (current)
		return (current->id);
	else
		return (-1);
}

t_queue	*queue_new(int id)
{
	t_queue *queue;

	if (!(queue = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	queue->id = id;
	queue->next = NULL;
	return (queue);
}

void	queue_delone(t_queue **queue)
{
	t_queue *tmp;

	if (!queue || !(*queue))
		return ;
	tmp = (*queue)->next;
	free(*queue);
	*queue = tmp;
}

void	queue_add(t_queue **queue, int id)
{
	t_queue *pos;

	if (!*queue)
	{
		*queue = queue_new(id);
		return ;
	}
	pos = *queue;
	while (pos->next)
		pos = pos->next;
	pos->next = queue_new(id);
}