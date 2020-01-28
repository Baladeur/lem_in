/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_BFS_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:28:24 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/28 18:44:40 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	**branch_exit(t_queue **queue, int **visited, int ***branch, int **r)
{
	if (queue && *queue)
		while (*queue)
			queue_delone(queue);
	if (visited && *visited)
	{
		free(*visited);
		*visited = NULL;
	}
	if (branch && *branch)
		destroy_matrix(branch);
	return (r);
}

static int	**branches(int **matrix, int *prev, int i, t_info *info)
{
	t_queue	*queue;
	int		**branch;
	int		*visited;
	int		current;
	int		iter;

	visited = NULL;
	branch = NULL;
	queue = NULL;
	if (!(visited = (int *)malloc(sizeof(int) * info->room_nb)))
		return (0);
	if (!(branch = init_matrix(info->room_nb)))
		return (branch_exit(NULL, &visited, NULL, 0));
	iter = -1;
	while (++iter < info->room_nb)
	{
		visited[iter] = iter == 0 || iter == i ? 1 : 0;
		prev[iter] = iter == i ? 1 : -1;
	}
	branch[0][i] = 1;
	branch[i][0] = -1;
	queue = queue_new(i);
	while (queue)
	{
		current = queue->id;
		queue_delone(&queue);
		iter = -1;
		while (++iter < info->room_nb)
		{
			if (matrix[current][iter] && !visited[iter] && iter != info->room_nb - 1)
			{
				visited[iter] = 1;
				prev[iter] = current;
				queue_add(&queue, iter);
			}
			if (matrix[current][iter] && iter != prev[current])
			{
				branch[current][iter]++;
				branch[iter][current]--;
			}
		}
	}
	return (branch_exit(NULL, &visited, NULL, branch));
}

static int	deadends(int **branch, int i, t_info *info)
{
	int c;
	int links;

	if (!i)
		return (0);
	if (i == info->room_nb - 1)
		return (1);
	c = -1;
	links = 0;
	while (++c < info->room_nb)
	{
		if (branch[c][i] > 0 && !deadends(branch, c, info))
		{
			branch[c][i] = 0;
			branch[i][c] = 0;
		}
		else if (branch[c][i] > 0)
			links++;
	}
	return (links);
}

int			**pre_BFS_cleaner(int **matrix, t_info *info)
{
	int	**directed;
	int **branch;
	int *prev;
	int i;

	directed = NULL;
	if (!(directed = init_matrix(info->room_nb)))
		return (NULL);
	if (!(prev = (int *)malloc(sizeof(int) * info->room_nb)))
		return (NULL);
	i = -1;
	while (++i < info->room_nb)
		if (matrix[0][i])
		{
			if (!(branch = branches(matrix, prev, i, info)))
				return (destroy_matrix(&directed));
			deadends(branch, i, info);
			//SOMME DE LA BRANCHE AVEC LA MATRICE ACTUELLE;
			destroy_matrix(&branch);
		}
	return (directed);
}