/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:59:26 by myener            #+#    #+#             */
/*   Updated: 2020/03/03 16:57:50 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	ant_free(t_info *info)
{
	int i;

	i = 0;
	while (i < info->ant_nb)
	{
		free(info->ant[i].path);
		i++;
	}
	// info->ant ? free(info->ant) : 0;
}

int		**matrix_free(int ***matrix, int count)
{
	int i;

	i = -1;
	while (++i < count)
		free(**matrix + i);
	free(*matrix);
	*matrix = NULL;
	return (NULL);
}

t_path	*path_free(t_path **path, int b)
{
	int	i;

	if (!path || *path)
		return (NULL);
	i = -1;
	while (b && path[0][++i].len > 0)
		if (path[0][i].edges)
			free(path[0][i].edges);
	free(path[0]);
	path[0] = NULL;
	return (NULL);
}

void	room_free(t_info *info)
{
	int i;

	i = 0;
	while (i < info->room_nb)
	{
		free(info->room_tab[i].name);
		i++;
	}
	info->room_tab ? free(info->room_tab) : 0;
}
