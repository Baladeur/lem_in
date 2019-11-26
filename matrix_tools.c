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
**	first NULL int*. Will leak if there is a NULL int* in between the allocated
**	int*
*/

int	**destroy_matrix(int ***matrix)
{
	int i;
	
	i = 0;
	while (**matrix + i)
	{
		free(**matrix + i);
		**matrix + i = NULL;
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

/*
**	Allocates an int** matrix of size count*count.
*/

int	**init_matrix(int count)
{
	int	**matrix;
	int i;

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
	return (matrix);
}
