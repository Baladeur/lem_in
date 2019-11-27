/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:10:44 by tferrieu          #+#    #+#             */
/*   Updated: 2019/11/26 18:10:45 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	If the given line matches the link syntax, it will be stored in room and
**	return 1. Returns 0 otherwise.
**	Link syntax : room1-room2
*/

static int	get_link(char *line, char **rooms, t_room **farm, int count)
{
	int orig;
	int dest;
	int curr;
	int len;
	int id;

	curr = 0;
	dest = -1;
	while (curr < count)
	{
		len = ft_strlen(farm[curr]->name);
		id = find_room(farm, line + len + 1);
		if (ft_strstr(line, farm[curr]->name) == line && line[len] == '-'	//	Check if the current room name match the first part of the link and is followed by '-'
			&& id > -1 && id != curr && (dest == -1							//	Check if the second part of the link is an existing room different from the current one
			|| ft_strlen(farm[curr]->name) > ft_strlen(farm[orig]->name))	//	Check if the link has priority over the previously stored one : longer room1 name.
			&& (dest = id) >= 0)
			orig = curr;
		curr++;
	}
	if (dest < 0 || !(*rooms = (char *)malloc(sizeof(char) * ft_strlen(line))))
		return (0);
	ft_strcpy(*rooms, farm[orig]->name);
	(*rooms)[ft_strlen(farm[orig]->name)] = 0;
	ft_strcpy(*rooms + ft_strlen(farm[orig]->name) + 1, farm[dest]->name);
	return (1);
}

/*
**	Returns the adjency matrix (int **) matching the given data or NULL if the
**	data isn't valid.
*/

int	**adj_matrix(char **data, t_room **farm, int count, int start)
{
	char	*rooms;
	int		**matrix;
	int		id1;
	int		id2;
	int		i;

	if (!(matrix = init_matrix(count)))
		return (NULL);
	i = start;
	while (data[i])
	{
		if (get_link(data[i], &rooms, farm, count))
		{
			id1 = find_room(farm, rooms);
			id2 = find_room(farm, rooms + ft_strlen(rooms) + 1);
			matrix[id1][id2] = 1;
			matrix[id2][id1] = 1;
		}
		else
			return (destroy_matrix(&matrix));
		i++;
	}
	return (matrix);
}
