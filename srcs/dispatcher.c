/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:22:11 by myener            #+#    #+#             */
/*   Updated: 2020/02/11 16:48:21 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

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

void			lem_in_dispatcher(t_info *info, t_path *path_tab)
{
	int		a; // current ant's ID.
	int		i; // index.
	int		j; // second index.
	int		n; // index in path_tab's edges.
	char	*room_name; // pretty self-explanatory.

	info->path_nb = 1; // for testing with map_1
	a = 0; // ants IDs start at 1, but we took care of it earlier so that it doesn't affect iteration.
	n = 0;
	i = 0;
	j = 0;
	room_name = NULL;
	while (!is_end_room(info->ant[info->ant_nb - 1].pos, info)) // while the last ant isn't in the end room,
	{
		i = 0; // reinitializes index every level.
		a = 0; // goes back to ant 1 after the iteration.
		while (i < info->path_nb && (room_is_empty(info, path_tab[i].edges[n]) || is_end_room(path_tab[i].edges[n], info))) // while there's an empty room on this level,
		{
			j = 0;
			if (info->ant[a].path[n] == path_tab[i].edges[n]) // if the current path is the same as the ant's path (& room is empty), then let's occupy it.
			{
				info->ant[a].pos = info->ant[a].path[n];
				room_name = get_room_name(info, info->ant[a].path[n]);
				room_name && path_tab[i].edges[n] > 0 ? ft_printf("L%d-%s ", info->ant[a].id, room_name) : 0; // this is bad and you (me) should feel bad
				a++;
			}
			j = n - 1; // set j to the room right before.
			while (a < info->ant_nb && path_tab[i].edges[j] > 0 && j > 0 && room_is_empty(info, path_tab[i].edges[j])) // while the room j is on is empty and isn't START
			{
				if (info->ant[a].path[j] == path_tab[i].edges[j])
				{
					info->ant[a].pos = info->ant[a].path[j];
					room_name = get_room_name(info, info->ant[a].path[j]);
					room_name && path_tab[i].edges[j] > 0 ? ft_printf("L%d-%s ", info->ant[a].id, room_name) : 0; // this is bad and you (me) should feel bad
					a++;
				}
				j--;
			}
			i++; // this path is filled, let's move on.
		}
		a != 0 ? ft_putchar('\n') : 0; // separates the turns displayed.
		n++; // that level of the path is now full, let's look further.
	}
}
