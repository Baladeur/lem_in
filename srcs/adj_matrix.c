/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:10:44 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/18 18:59:01 by tferrieu         ###   ########.fr       */
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

	i = 0;
	while (i < info->room_nb)
	{
		if (!(ft_strcmp(info->room_tab[i].name, name)))
			return (i);
		i++;
	}
	return (-1);
}

static int	get_link(char *line, char **rooms, t_info *info)
{
	int orig;
	int dest;
	int curr;
	int len;
	int id;

	curr = -1;
	dest = -1;
	while (++curr < info->room_nb)
	{
		len = ft_strlen(info->room_tab[curr].name);
		id = find_room(line + len + 1, info);
		if (ft_strstr(line, info->room_tab[curr].name) == line
			&& line[len] == '-' && id > -1 && id != curr && (dest == -1
			|| ft_strlen(info->room_tab[curr].name)
			> ft_strlen(info->room_tab[orig].name)) && (dest = id) >= 0)
			orig = curr;
	}
	if (dest < 0 || !(*rooms = (char *)malloc(sizeof(char) * ft_strlen(line))))
		return (0);
	ft_strcpy(*rooms, info->room_tab[orig].name);
	(*rooms)[ft_strlen(info->room_tab[orig].name)] = 0;
	ft_strcpy(*rooms + ft_strlen(info->room_tab[orig].name) + 1,
		info->room_tab[dest].name);
	return (1);
}

/*
**	Stores the adjency matrix (int **) matching the given data in the info.
**	Returns 1 if the operation is successfull, 0 otherwise.
*/

int			adj_matrix(char **data, t_info *info, int start)
{
	char	*rooms;
	int		id1;
	int		id2;
	int		i;

	if (!(info->matrix = init_matrix(info->room_nb)))
		return (0);
	i = start;
	while (data[i])
	{
		if (get_link(data[i], &rooms, info))
		{
			id1 = find_room(rooms, info);
			id2 = find_room(rooms + ft_strlen(rooms) + 1, info);
			info->matrix[id1][id2] = 1;
			info->matrix[id2][id1] = 1;
		}
		else if (!(destroy_matrix(&(info->matrix), info->room_nb)))
			return (0);
		i++;
	}
	return (1);
}
