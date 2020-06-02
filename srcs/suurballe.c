/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 18:26:17 by tferrieu          #+#    #+#             */
/*   Updated: 2020/06/02 18:01:02 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	**adj_split(t_info *info)
{
	int	**matrix;
	int	x;
	int	y;

	if (!(matrix = init_matrix(info->room_nb * 2 - 2)))
		return (0);
	y = -1;
	while ((x = -1) && ++y < info->room_nb)
		while (++x < info->room_nb)
			if (info->matrix[y][x] && x && y != info->room_nb - 1)
				matrix[y * 2][x * 2 - 1] = 1;
	x = 0;
	while (++x < info->room_nb - 1)
		matrix[x * 2 - 1][x * 2] = 1;
	return (matrix);
}

static void	reverse_path(int **matrix, int *curr, t_info *info)
{
	int pos;

	pos = info->room_nb * 2 - 3;
	while (pos)
	{
		matrix[pos][curr[pos]] = 1;
		matrix[curr[pos]][pos] = 0;
		pos = curr[pos];
	}
}

static int	suur_exit(int ***matrix, int ***map, t_elist **edges, t_info *info)
{
	if (matrix && *matrix)
		matrix_free(matrix, info->room_nb * 2 - 2);
	if (map && *map)
		matrix_free(map, info->room_nb);
	if (edges && *edges)
		while (*edges)
			elist_delone(edges, 1);
	return (0);
}

int			suurballe(t_info *info, t_path **best)
{
	t_elist	*edges;
	int		**matrix;
	int		**map;
	int		*curr;

	edges = NULL;
	if (!(matrix = adj_split(info)))
		return (0);
	if (!(map = init_matrix(info->room_nb)))
		return (suur_exit(&matrix, NULL, NULL, info));
	while ((curr = suurbfs(matrix, info)))
	{
		info->path_nb++;
		if (!(elist_add(&edges, curr))
			|| !(overlap_handler(edges, map, info, best)))
			return (suur_exit(&matrix, &map, &edges, info));
		reverse_path(matrix, curr, info);
	}
	suur_exit(&matrix, &map, &edges, info);
	return (1);
}
