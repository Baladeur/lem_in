/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:59:26 by myener            #+#    #+#             */
/*   Updated: 2020/03/12 17:06:36 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		string_free(char *str, int ret)
{
	str ? free(str) : 0;
	return (ret);
}

void	ant_free(t_info *info)
{
	int i;

	i = 0;
	while (i < info->ant_nb)
	{
		free(info->ant[i].path);
		i++;
	}
	info->ant ? free(info->ant) : 0;
}

int		**matrix_free(int ***matrix, int count)
{
	int i;

	if (!matrix || !(*matrix))
		return (NULL);
	i = -1;
	while (++i < count)
		if ((*matrix)[i])
			free((*matrix)[i]);
	free(*matrix);
	*matrix = NULL;
	return (NULL);
}

t_path	*path_free(t_path **path, int b)
{
	int	i;

	if (!path || !(*path))
		return (NULL);
	i = -1;
	while ((*path)[++i].len >= 0)
		if (b && (*path)[i].edges)
			free((*path)[i].edges);
	free((*path)[i].edges);
	free((*path));
	(*path) = NULL;
	return (NULL);
}

void	room_free(t_info *info)
{
	int i;

	i = 0;
	while (i < info->room_nb)
	{
		if (info->room_tab[i].name)
			free(info->room_tab[i].name);
		i++;
	}
	free(info->room_tab);
}
