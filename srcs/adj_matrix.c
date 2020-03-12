/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:10:44 by tferrieu          #+#    #+#             */
/*   Updated: 2020/03/12 18:09:46 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
**	If the given line matches the link syntax, it will be stored in room and
**	return 1. Returns 0 otherwise.
**	Link syntax : room1-room2
*/

static int	find_room(char *name, t_info *info)
{
	int i;

	i = -1;
	while (++i < info->room_nb)
		if (!(ft_strcmp(info->room_tab[i].name, name)))
			return (i);
	return (-1);
}

/*
** If the line has a correct link formatting, returns 1 and replaces
** the '-' with a 0 to split the link in two. Returns 0 otherwise.
*/

static int	get_link(char *line, t_info *info)
{
	int i;

	i = -1;
	while (line[++i])
		if (line[i] == '-')
		{
			line[ft_strlen(line) - 1] = 0;
			line[i] = 0;
			break ;
		}
	if (line[i - 1] == '\n')
		return (0);
	if (!(ft_strcmp(line, line + ft_strlen(line) + 1))
		|| find_room(line, info) < 0
		|| find_room(line + ft_strlen(line) + 1, info) < 0)
	{
		line[i] = '-';
		line[ft_strlen(line)] = '\n';
		return (0);
	}
	return (1);
}

/*
** Gets the position of the first link
*/

static int	get_link_start(char **data, t_info *info)
{
	int i;

	i = info->rooms_line + 1;
	while (is_room(data[i]))
		i++;
	return (i);
}

/*
**	Stores the adjency matrix (int **) matching the given data in the info.
**	Returns 1 if the operation is successfull, 0 otherwise.
*/

int			adj_matrix(char **data, t_info *info)
{
	int		id1;
	int		id2;
	int		i;

	if (!(i = get_link_start(data, info)))
		return (0);
	if (!(info->matrix = init_matrix(info->room_nb)))
		return (0);
	while (data[i] && i < info->edges_line)
	{
		if (get_link(data[i], info))
		{
			id1 = find_room(data[i], info);
			id2 = find_room(data[i] + ft_strlen(data[i]) + 1, info);
			info->matrix[id1][id2] = 1;
			info->matrix[id2][id1] = 1;
			data[i][ft_strlen(data[i])] = '-';
			data[i][ft_strlen(data[i])] = '\n';
		}
		else if (!(data[i][0] == '#'))
			return (1);
		i++;
	}
	return (1);
}
