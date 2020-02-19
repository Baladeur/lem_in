/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:28:24 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/19 17:17:12 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Returns 1 if every room explored during the turn aren't in the queue anymore.
*/

static int		is_turn_over(t_branch *branch, int turn)
{
	t_queue *current;

	current = branch->queue;
	while (current)
	{
		if (branch->visited[current->id] == turn)
			return (0);
		current = current->next;
	}
	return (1);
}

/*
** The loop used by the branching algorithm. Check every connection to the
** currently queued room and updates the branching matrix accordingly.
*/

static int		branching_loop(int **matrix, t_branch *branch, int turn)
{
	int		current;
	int		iter;

	current = branch->queue->id;
	iter = -1;
	while (++iter < branch->size)
	{
		if (matrix[current][iter] && branch->visited[iter] < 0
			&& iter != branch->size - 1)
		{
			branch->visited[iter] = turn + 1;
			if (!(queue_add(&(branch->queue), iter)))
				return (0);
		}
		else if (matrix[current][iter] && branch->visited[iter] == turn + 1
			&& iter != branch->size - 1)
			branch->weight[iter]++;
		if (matrix[current][iter] && (!branch->matrix[current][iter]
		|| branch->visited[iter] == branch->visited[current]))
		{
			branch->matrix[current][iter] += branch->weight[current];
			branch->matrix[iter][current] -= branch->weight[current];
		}
	}
	return (1);
}

/*
** Explores the adjacency matrix to create a directed branching matrix.
*/

static t_branch	*branching(int **matrix, t_branch *branch)
{
	int		turn;

	turn = 1;
	while (branch->queue)
	{
		if (!branching_loop(matrix, branch, turn))
			return (destroy_branching(&branch));
		queue_delone(&(branch->queue));
		if (is_turn_over(branch, turn))
			turn++;
	}
	return (branch);
}

/*
** Remove dead ends from a directed branching matrix.
*/

static int		deadends(int **branch, int i, int size)
{
	int c;
	int links;

	if (!i)
		return (0);
	if (i == size - 1)
		return (1);
	c = -1;
	links = 0;
	while (++c < size)
	{
		if (branch[i][c] > 0 && !deadends(branch, c, size))
		{
			branch[c][i] = 0;
			branch[i][c] = 0;
		}
		else if (branch[i][c] > 0)
			links++;
	}
	return (links);
}

/*
** Turns an adjacency matrix graph into a directed graph.
*/

int				directed_matrix(t_info *info)
{
	t_branch	*branch;
	int			i;

	branch = NULL;
	if (!(info->dir_matrix = init_matrix(info->room_nb))
		|| !(branch = init_branching(info->room_nb)))
		return (0);
	i = -1;
	while (++i < info->room_nb)
	{
		if (info->matrix[0][i])
		{
			reset_branching(&branch, i);
			if (!(branching(info->matrix, branch))
				&& !(matrix_free(&(info->dir_matrix), info->room_nb)))
				return (0);
			deadends(branch->matrix, i, info->room_nb);
			sum_matrix(info->dir_matrix, branch->matrix, info->room_nb);
		}
	}
	destroy_branching(&branch);
	return (fill_gaps(info));
}
