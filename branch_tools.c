/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:20:38 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/29 17:11:37 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_branch	*init_branching(int size)
{
	t_branch	*branch;
	int			y;

	if (!(branch = (t_branch *)malloc(sizeof(t_branch))))
		return (NULL);
	branch->visited = NULL;
	branch->matrix = NULL;
	branch->queue = NULL;
	branch->prev = NULL;
	branch->size = size;
	if (!(branch->prev = (int *)malloc(sizeof(int) * size)))
		return (destroy_branching(&branch));
	if (!(branch->visited = (int *)malloc(sizeof(int) * size)))
		return (destroy_branching(&branch));
	if (!(branch->matrix = (int **)malloc(sizeof(int *) * size)))
		return (destroy_branching(&branch));
	y = -1;
	while (++y < size)
		branch->matrix[y] = NULL;
	y = -1;
	while (++y < size)
		if (!(branch->matrix[y] = (int *)malloc(sizeof(int) * size)))
			return (destroy_branching(&branch));
	return (branch);
}

t_branch	*reset_branching(t_branch **branch, int i)
{
	int	x;
	int	y;

	if (!(branch[0]->queue = queue_new(i)))
		return (destroy_branching(branch));
	y = -1;
	while (++y < branch[0]->size)
	{
		branch[0]->prev[y] = y == i ? 0 : -1;
		branch[0]->visited[y] = y == i || y == 0 ? 1 : 0;
	}
	y = -1;
	while (++y < branch[0]->size && (x = -1))
		while (++x < branch[0]->size)
			branch[0]->matrix[y][x] = 0;
	branch[0]->matrix[0][i] = 1;
	branch[0]->matrix[i][0] = -1;
	return (*branch);
}

t_branch	*destroy_branching(t_branch **branch)
{
	if (!branch || !*branch)
		return (NULL);
	if (branch[0]->prev)
		free(branch[0]->prev);
	if (branch[0]->visited)
		free(branch[0]->visited);
	if (branch[0]->matrix)
		destroy_matrix(&(branch[0]->matrix));
	if (branch[0]->queue)
		while (branch[0]->queue)
			queue_delone(&(branch[0]->queue));
	branch[0]->visited = NULL;
	branch[0]->matrix = NULL;
	branch[0]->queue = NULL;
	branch[0]->prev = NULL;
	branch[0] = NULL;
	return (NULL);
}