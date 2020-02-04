/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_BFS_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:28:24 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/04 17:19:55 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

static t_branch	*branching(int **matrix, t_branch *branch, int i)
{
	int		current;
	int		iter;
	int		turn;

	turn = 1;
	while (branch->queue)
	{
		current = branch->queue->id;
		queue_delone(&(branch->queue));
		iter = -1;
		while (++iter < branch->size)
		{
			if (matrix[current][iter] && branch->visited[iter] < 0 && iter != branch->size - 1)
			{
				branch->visited[iter] = turn + 1;
				if (!(queue_add(&(branch->queue), iter)))
					return (destroy_branching(&branch));
			}
			else if (matrix[current][iter] && branch->visited[iter] == turn + 1 && iter != branch->size - 1)
				branch->weight[iter]++;
			if (matrix[current][iter] && (!branch->matrix[current][iter]
			|| branch->visited[iter] == branch->visited[current]))
			{
				branch->matrix[current][iter] += branch->weight[current];
				branch->matrix[iter][current] -= branch->weight[current];
			}
		}
		if (is_turn_over(branch, turn))
			turn++;
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

int				**pre_cleaner(int **matrix, t_info *info)
{
	t_branch	*branch;
	int			**directed;
	int			i;

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
			printf("Start : %d\n", i);
			reset_branching(&branch, i);
			if (!(branching(matrix, branch, i)))
				return (destroy_matrix(&directed));
			printf("Branching :\n");
			print_matrix(branch->matrix, branch->size);
			deadends(branch->matrix, i, info->room_nb);
			printf("Dead Ends :\n");
			print_matrix(branch->matrix, branch->size);
			printf("\n\n\n");
			sum_matrix(directed, branch->matrix, info->room_nb);
		}
	destroy_branching(&branch);
	return (directed);
}
