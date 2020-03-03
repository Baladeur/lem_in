/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:08:50 by tferrieu          #+#    #+#             */
/*   Updated: 2020/03/03 16:05:48 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		**init_matrix(int count)
{
	int	**matrix;
	int i;
	int j;

	i = -1;
	matrix = NULL;
	if (!(matrix = (int **)malloc(sizeof(int *) * count)))
		return (NULL);
	while (++i < count)
	{
		matrix[i] = NULL;
		if (!(matrix[i] = (int *)malloc(sizeof(int) * count)))
			return (matrix_free(&matrix, count));
	}
	j = -1;
	while (++j < count)
	{
		i = -1;
		while (++i < count)
			matrix[j][i] = 0;
	}
	return (matrix);
}

int		**dupe_matrix(int **matrix, int count)
{
	int	**new;
	int x;
	int y;

	new = NULL;
	if (!(new = (int **)malloc(sizeof(int *) * count)))
		return (NULL);
	x = -1;
	while (++x < count && !(new[x] = NULL))
		if (!(new[x] = (int *)malloc(sizeof(int) * count)))
			return (matrix_free(&new, count));
	y = -1;
	while (++y < count && (x = -1))
		while (++x < count)
			new[y][x] = matrix[y][x];
	return (new);
}

void	sum_matrix(int **dest, int **src, int size)
{
	int x;
	int y;

	y = -1;
	while (++y < size && (x = -1))
		while (++x < size)
			dest[y][x] += src[y][x];
}

void	print_matrix(int **matrix, int count)
{
	int x;
	int y;

	y = -1;
	while (++y < count)
	{
		x = -1;
		while (++x < count)
			printf("%2d ", matrix[y][x]);
		printf("\n");
	}
}
