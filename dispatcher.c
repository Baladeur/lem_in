/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:22:11 by myener            #+#    #+#             */
/*   Updated: 2020/01/28 17:52:53 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

static char		*get_room_name(t_info *info, int room_id, t_room *room_tab) // retrieves the room's name from id.
{
	int	i;

	i = 0;
	while (i < info->room_nb) // while we go through the rooms,
	{
		if (room_id == room_tab[i].id) // if the ID we have matches one of the rooms',
			return (room_tab[i].name); // then we need said room's name: return it.
		i++;
	}
	return (NULL); // otherwise the ID doesn't match any room and there's an error ; return NULL.
}

// static int		is_in_end_room(t_ant ant, int room_nb, t_room *room_tab)
// {
// 	int i;

// 	i = 0;
// 	while (i < room_nb) // while we go through the rooms,
// 	{
// 		if (room_tab[i].type == 'e') // if the room type is 'e',
// 			break ; // then it's the end room ; we must stay on it, so break.
// 		i++;
// 	}
// 	if (ant.pos == room_tab[i].id) // if the ant is on end, return 1.
// 		return (1);
// 	return (0);
// }

void			lem_in_dispatcher(t_info *info, t_path *path_tab, t_room *room_tab)
{
	int		a; // current ant's ID.
	int		i; // index.
	// int		tmp; // tmp int to stock n.
	int		n; // index in path_tab.
	char	*room_name; // pretty self-explanatory.

	info->path_nb = 1; // for testing with map_1
	a = 0; // ants IDs start at 1, but we took care of it earlier so that it doesn't affect iteration.
	n = 0;
	room_name = NULL;
	while (n < 10 /*<- debug */ && info->ant[info->ant_nb - 1].pos != room_tab[info->room_nb - 1].id) // while last ant isn't in end room,
	{
		i = 0;
		a = 0; // goes back to ant 1 after the iteration.
		printf("n = %d\n", n);
		while (i < info->path_nb && a < info->ant_nb && room_is_empty(info, path_tab[i].edges[n])) // while there's an empty room on this level,
		{
			printf("ant = %d\n", a + 1);
			if (info->ant[a].path[n] == path_tab[i].edges[n]) // if the current path is the same as the ant's path (& room is empty), then let's occupy it.
			{
				info->ant[a].pos = info->ant[a].path[n];
				room_name = get_room_name(info, n, room_tab);
				ft_printf("L%d-%s ", info->ant[a].id, room_name);
				i++; // this path is filled, let's move on.
				a++;
			}
			// tmp = n; // initialize m to where we were in the path_tab just now.
			// while (n != path_tab[i].edges[0]) // while m didn't reach the START room,
			// {
			// 	if (room_is_empty(info, path_tab[i].edges[n])) // if the room is empty, get it.
			// 	{
			// 		info->ant[a].pos = info->ant[a].path[n];
			// 		room_name = get_room_name(info, n, room_tab);
			// 		ft_printf("L%d-%s ", info->ant[a].id, room_name);
			// 		a++;
			// 	}
			// 	n--; // decrement m.
			// }
			// n = tmp;
			// if (is_in_end_room(info->ant[a], info->room_nb, room_tab)) // while the ant we're on is on the end room already, ignore (let them stay there).
			// 	a++;
		}
		n++; // that level of the path is now full, let's look further.
		ft_putchar('\n'); // separates the levels displayed.
	}
	exit (0); // debug
}
