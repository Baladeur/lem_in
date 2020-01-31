/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_BFS_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:28:24 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/31 17:16:35 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_branch	*branching(int **matrix, t_branch *branch, int i)
{
	int		current;
	int		iter;

	while (branch->queue)
	{
		current = branch->queue->id;
		queue_delone(&(branch->queue));
		iter = -1;
		while (++iter < branch->size)
		{
			if (matrix[current][iter] && !branch->visited[iter] && iter != branch->size - 1 &&iter != branch->prev[current])
			{
				branch->visited[iter] = 1;
				branch->prev[iter] = current;
				if (!(queue_add(&(branch->queue), iter)))
					return (destroy_branching(&branch));
			}
			if (matrix[current][iter] && iter != branch->prev[current])
			{
				branch->matrix[current][iter]++;
				branch->matrix[iter][current]--;
			}
		}
	}
	return (branch);
}

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

int				**pre_BFS_cleaner(int **matrix, t_info *info)
{
	t_branch	*branch;
	int			**directed;
	int 		i;

	directed = NULL;
	branch = NULL;
	if (!(directed = init_matrix(info->room_nb)))
		return (NULL);
	if (!(branch = init_branching(info->room_nb)))
		return (NULL);
	i = -1;
	while (++i < info->room_nb)
		if (matrix[0][i])
		{
			reset_branching(&branch, i);
			if (!(branching(matrix, branch, i)))
				return (destroy_matrix(&directed));
			deadends(branch->matrix, i, info->room_nb);
			sum_matrix(directed, branch->matrix, info->room_nb);
		}
	destroy_branching(&branch);
	return (directed);
}