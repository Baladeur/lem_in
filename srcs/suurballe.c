/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 18:26:17 by tferrieu          #+#    #+#             */
/*   Updated: 2020/05/22 22:32:07 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	**adj_split(t_info *info)
{
	int	**new;
	int i;
	int j;

	new = NULL;
	if (!(new = init_matrix(info->room_nb * 3 - 4)))
		return (NULL);
	j = -1;
	while (++j < info->room_nb && (i = -1))
		while (++i < info->room_nb)
			if (info->matrix[j][i])
			{
				new[j > 1 ? j * 3 - 2 : j][i > 1 ? i * 3 - 2 : i] = 1;
				new[i > 1 ? i * 3 - 2 : i][j > 1 ? j * 3 - 2 : j] = 1;
			}
	return (new);
}

static void	split_node(int **matrix, int node, int *curr, t_info *info)
{
	int next;
	int i;

	i = info->room_nb * 3 - 5;
	while ((i = curr[i]))
		if (curr[i] == node && (next = curr[i]))
			break ;
	i = -1;
	while (++i < info->room_nb * 3 - 4)
	{
		if (matrix[node][i] && i != next && i != curr[node])
		{
			matrix[node + 1][i] = -1;
			matrix[node + 2][i] = 1;
			matrix[i][node + 1] = 1;
			matrix[i][node + 2] = -1;
			matrix[node + 1][node + 2] = -1;
			matrix[node + 2][node + 1] = 1;
		}
		if (matrix[node][i])
		{
			matrix[node][i] = 0;
			matrix[i][node] = 0;
		}
	}
}

static void	extend_path(int **matrix, int *curr, t_info *info)
{
	int pos;
	int src;
	int dst;

	pos = info->room_nb * 3 - 5;
	while ((pos = curr[pos]))
		if (!((pos - 1) % 3))
			split_node(matrix, pos, curr, info);
	pos = info->room_nb * 3 - 5;
	matrix[pos][(curr[pos] - 1) % 3 ? curr[pos] : curr[pos] + 2] = 1;
	matrix[(curr[pos] - 1) % 3 ? curr[pos] : curr[pos] + 2][pos] = -1;
	while ((pos = curr[pos]))
	{
		dst = (curr[pos] - 1) % 3 ? curr[pos] : curr[pos] + 2;
		src = (pos - 1) % 3 ? pos : pos + 1;
		matrix[src][dst] = 1;
		matrix[dst][src] = -1;
	}
	matrix[0][(pos - 1) % 3 ? pos : pos + 1] = -1;
	matrix[(pos - 1) % 3 ? pos : pos + 1][0] = 1;
}

static int	suur_exit(int ***matrix, int ***res, t_elist **paths, t_info *info)
{
	if (matrix && *matrix)
		matrix_free(matrix, info->room_nb * 3 - 4);
	if (res && *res)
		matrix_free(res, info->room_nb);
	if (paths && *paths)
		while (*paths)
			elist_delone(paths, 1);
	return (0);
}

int			suurballe(t_info *info, t_path **best)
{
	t_elist	*paths;
	int		**matrix;
	int		**res;
	int		*curr;

	paths = NULL;
	curr = NULL;
	if (!(matrix = adj_split(info)))
		return (0);
	if (!(res = init_matrix(info->room_nb)))
		return (suur_exit(&matrix, NULL, NULL, info));
	while ((curr = suurbfs(matrix, info)))
	{
		info->path_nb++;
		if (!(elist_add(&paths, curr))
			|| !(overlap_handler(paths, res, info, best)))
			return (suur_exit(&matrix, &res, &paths, info));
		extend_path(matrix, curr, info);
	}
	suur_exit(&matrix, &res, &paths, info);
	return (1);
}
