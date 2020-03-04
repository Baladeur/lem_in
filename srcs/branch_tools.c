/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   branch_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:20:38 by tferrieu          #+#    #+#             */
/*   Updated: 2020/03/04 19:16:03 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Initializes the branch structure used by the directed matrix.
** Empty by default, values must be set for each branching.
** size = Ant farm's size (info->room_nb)
*/

t_branch	*init_branching(int size)
{
	t_branch	*branch;
	int			y;

	if (!(branch = (t_branch *)malloc(sizeof(t_branch))))
		return (NULL);
	branch->visited = NULL;
	branch->matrix = NULL;
	branch->weight = NULL;
	branch->queue = NULL;
	branch->size = size;
	if (!(branch->visited = (int *)malloc(sizeof(int) * size))
		|| !(branch->weight = (int *)malloc(sizeof(int) * size))
		|| !(branch->matrix = (int **)malloc(sizeof(int *) * size)))
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

/*
** Sets the values of an initialized branch stucture starting at i.
** i must be linked to the start room for the algorithm to work properly.
*/

t_branch	*reset_branching(t_branch **branch, int i)
{
	int	x;
	int	y;

	if (!((*branch)->queue = queue_new(i)))
		return (destroy_branching(branch));
	y = -1;
	while (++y < (*branch)->size)
		(*branch)->visited[y] = -1;
	y = -1;
	while (++y < (*branch)->size)
		(*branch)->weight[y] = 1;
	(*branch)->visited[0] = 0;
	(*branch)->visited[i] = 1;
	y = -1;
	while (++y < (*branch)->size && (x = -1))
		while (++x < (*branch)->size)
			(*branch)->matrix[y][x] = 0;
	(*branch)->matrix[0][i] = 1;
	(*branch)->matrix[i][0] = -1;
	return (*branch);
}

/*
** Free the memory used by a branch stucture.
*/

t_branch	*destroy_branching(t_branch **branch)
{
	int x;

	if (!branch || !*branch)
		return (NULL);
	if ((*branch)->visited)
		free((*branch)->visited);
	if ((*branch)->weight)
		free((*branch)->weight);
	if ((*branch)->matrix && (x = -1))
		matrix_free(&((*branch)->matrix), (*branch)->size);
	if ((*branch)->queue)
		while ((*branch)->queue)
			queue_delone(&((*branch)->queue));
	free(*branch);
	*branch = NULL;
	return (NULL);
}
