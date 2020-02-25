/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:22:11 by myener            #+#    #+#             */
/*   Updated: 2020/02/25 15:56:00 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

char			*get_room_name(t_info *info, int room_id) // retrieves the room's name from id.
{
	int	i;

	i = 0;
	while (i < info->room_nb) // while we go through the rooms,
	{
		if (room_id == info->room_tab[i].id) // if the ID we have matches one of the rooms',
			return (info->room_tab[i].name); // then we need said room's name: return it.
		i++;
	}
	return (NULL); // otherwise the ID doesn't match any room and there's an error ; return NULL.
}

static int		room_is_empty(t_info *info, int room_id) // checks if an ant is already in room_id's room.
{
	int	i;

	i = 0;
	while (i < info->ant_nb) // while we go through the ants,
	{
		if (info->ant[i].pos == room_id) // if one of them is positioned on the room,
			return (0); // then it's not empty ; return 0.
		i++;
	}
	return (1); // otherwise, if none is, the room is empty ; return 1.
}

static int		is_end_room(int room_id, t_info *info)
{
	int i;

	i = 0;
	while (i < info->room_nb) // while we go through the rooms,
	{
		if (info->room_tab[i].type == 'e') // if the room type is 'e',
			break ; // then it's the end room ; we must stay on it, so break.
		i++;
	}
	if (room_id == info->room_tab[i].id) // if the room ID matches end's, return 1.
		return (1);
	return (0);
}

void			lem_in_dispatcher(t_info *info, t_path *path_tab)
{
	int		a; // current ant's ID.
	int		i; // path index.
	int		j; // second index.
	int		n; // index in path_tab's edges.
	char	*room_name; // pretty self-explanatory.

	// info->path_nb = 1; // for testing with map_1
	a = 0; // ants IDs start at 1, but we took care of it earlier so that it doesn't affect iteration.
	n = 0;
	i = 0;
	j = 0;
	room_name = NULL;
	while (path_tab[i].edges[n] >= 0 && !is_end_room(info->ant[info->ant_nb - 1].pos, info)) // while the last ant isn't in the end room, there's still work to do.
	{
		// ft_putchar('1');
		i = 0; // reinitializes path index every level.
		while (i < info->path_nb && (room_is_empty(info, path_tab[i].edges[n]) || is_end_room(path_tab[i].edges[n], info))) // while room on this level is empty OR is end room (can fit all ants),
		{
			// ft_putchar('2');
			j = 0;
			a = 0;
			if (info->ant[a].path[n] == path_tab[i].edges[n]) // if the current path is the same as the ant's path (& room is empty), then let's occupy it.
			{
				// ft_putchar('A');
				info->ant[a].pos = info->ant[a].path[n];
				room_name = get_room_name(info, info->ant[a].path[n]);
				room_name ? ft_printf("L%d-%s ", info->ant[a].id, room_name) : 0; // was there a room_name at all ? if yes print it.
				a++;
			}
			j = n - 1; // set j to the room right before.
			// ft_printf("a = %d, j = %d\n", a, j); // debug
			while (a < info->ant_nb && j > 0 && room_is_empty(info, path_tab[i].edges[j])) // while the room j is on is empty and isn't START
			{
				// ft_putchar('3');
				// ft_putchar('B');
				if (info->ant[a].path[j] == path_tab[i].edges[j])
				{
					info->ant[a].pos = info->ant[a].path[j];
					room_name = get_room_name(info, info->ant[a].path[j]);
					room_name ? ft_printf("L%d-%s ", info->ant[a].id, room_name) : 0; // was there a room_name at all ? if yes print it.
					a++;
				}
				j--;
			}
			// ft_printf("i = %d, j = %d, a = %d, n = %d\n", i, j, a, n); // debug
			i++; // this path is filled, let's move on.
		}
		// ft_putchar('\n');
		a != 0 ? ft_putchar('\n') : 0; // separates the turns displayed.
		n++; // that level of the path is now full, let's look further.
	}
}
