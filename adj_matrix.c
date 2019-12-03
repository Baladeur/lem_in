/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adj_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:10:44 by tferrieu          #+#    #+#             */
/*   Updated: 2019/12/03 19:04:37 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	If the given line matches the link syntax, it will be stored in room and
**	return 1. Returns 0 otherwise.
**	Link syntax : room1-room2
*/

static int	get_link(char *line, char **rooms, t_room *farm)
{
	t_room	*curr;
	t_room	*orig;
	t_room	*dest;
	t_room	*curr2;
	int		len;

	curr = farm;
	dest = NULL;
	orig = NULL;
	while (curr)
	{
		len = ft_strlen(curr->name);
		curr2 = find_room(farm, line + len + 1);
		if (ft_strstr(line, curr->name) == line && line[len] == '-' && curr2
			&& curr2 != curr && (!dest || len > ft_strlen(orig->name)) &&
			(dest = curr2))
			orig = curr;
		curr = curr->next;
	}
	if (!dest || !(*rooms = (char *)malloc(sizeof(char) * ft_strlen(line))))
		return (0);
	ft_strcpy(*rooms, orig->name);
	(*rooms)[ft_strlen(orig->name)] = 0;
	ft_strcpy(*rooms + ft_strlen(orig->name) + 1, dest->name);
	return (1);
}

/*
**	Returns the adjency matrix (int **) matching the given data or NULL if the
**	data isn't valid.
*/

int			**adj_matrix(char **data, t_room *farm, int count, int start)
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
		if (get_link(data[i], &rooms, farm))
		{
			id1 = find_room(farm, rooms)->id;
			id2 = find_room(farm, rooms + ft_strlen(rooms) + 1)->id;
			matrix[id1][id2] = 1;
			matrix[id2][id1] = 1;
		}
		else
			return (destroy_matrix(&matrix));
		i++;
	}
	return (matrix);
}
