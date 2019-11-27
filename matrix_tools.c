/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:08:50 by tferrieu          #+#    #+#             */
/*   Updated: 2019/11/26 16:08:55 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Free the memory of an int** where every allocated int* is found before the
**	first NULL int*. Will leak if there is a NULL int* in-between the allocated
**	int*
*/

int	**destroy_matrix(int ***matrix)
{
	int i;

	i = 0;
	while (**matrix + i)
	{
		free(**matrix + i);
		i++;
	}
	free(*matrix);
	*matrix = NULL;
	return (NULL);
}

/*
**	Allocates an int** matrix of size count*count, setting each value at 0.
*/

int	**init_matrix(int count)
{
	int	**matrix;
	int i;
	int j;

	i = 0;
	matrix = NULL;
	if (!(matrix = (int **)malloc(sizeof(int *) * count)))
		return (NULL);
	while (i < count)
	{
		matrix[i] = NULL;
		if (!(matrix[i] = (int *)malloc(sizeof(int) * count)))
			return (destroy_matrix(&matrix));
		i++;
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

void	print_matrix(int **matrix, int count)
{
	int x;
	int y;

	y = 0;
	while (y < count)
	{
		x = 0;
		while (x < count)
		{
			ft_printf("%d ", matrix[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}