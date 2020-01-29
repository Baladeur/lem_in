/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:08:50 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/29 15:49:53 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Free the memory of an int** where every allocated int* is found before the
**	first NULL int*. Will leak if there is a NULL int* in-between the allocated
**	int*
*/

int		**destroy_matrix(int ***matrix)
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

int		**init_matrix(int count)
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

/*
**	Duplicates an existing matrix.
*/

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
			return (destroy_matrix(&new));
	y = -1;
	while (++y < count && (x = -1))
		while (++x < count)
			new[y][x] = matrix[y][x];
	return (new);
}


/*
**	Return a matrix that is the summ of two matrix of the same size.
**	if destroy is set to 1, it will also free both source matrix.
*/

int		**sum_matrix(int ***src1, int ***src2, int size, int destroy)
{
	int	**res;
	int x;
	int y;

	res = NULL;
	if (!(res = (int **)malloc(sizeof(int *) * size)))
		return (NULL);
	x = -1;
	while (++x < size && !(res[x] = NULL))
		if (!(res[x] = (int *)malloc(sizeof(int) * size)))
			return (destroy_matrix(&res));
	y = -1;
	while (++y < size && (x = -1))
		while (++x < size)
			res[y][x] = (*src1)[y][x] + (*src2)[y][x];
	if (destroy && destroy_matrix(src1) == NULL)
		destroy_matrix(src2);
	return (res);
}

/*
**	Displays the matrix of count*count size on standart outpout
*/

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
