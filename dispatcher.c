/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:22:11 by myener            #+#    #+#             */
/*   Updated: 2020/01/25 17:32:57 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		room_is_empty(t_info *info, int room_id) // checks if an ant is already in room_id's room.
{
	int	i;

	i = 0;
	while (i < info->ant_nb)
	{
		if (info->ant[i].pos == room_id)
			return (1);
		i++;
	}
	return (0);
}

static char		*get_room_name(t_info *info, int room_id, t_room *room_tab) // retrieves the room's name from id.
{
	int	i;

	i = 0;
	while (i < info->room_nb)
	{
		if (room_id == room_tab[i].id)
			return (room_tab[i].name);
		i++;
	}
	return (NULL);
}

void			lem_in_dispatcher(t_info *info, t_path *path_tab, t_room *room_tab)
{
	int		i; // index.
	int		a; // current ant's ID.
	int		n; // index in path_tab.
	char	*room_name; // pretty self-explanatory.

	a = 1; // 1 because ant IDs start at 1.
	n = 1; // 1 because we ignore the first (0) case of the tab as it is the start room.
	room_name = NULL;
	while (info->ant[info->ant_nb].pos != info->room_nb - 1) // while last ant isn't in end room, roll roll roll.
	{
		i = 0;
		a = 1; // goes back to ant 1 after the iteration.
		while (room_is_empty(info, path_tab[i].edges[n])) // while there's an empty room on this level of iteration, go through them.
		{
			printf("le segfault est qqupart par la, les if/while sont trop permissifs\n");
			if (info->ant[a].path[n] == path_tab[i].edges[n]) // if the current path is the same as the ant's path (& room is empty), then let's occupy it.
			{
				info->ant[a].pos = info->ant[a].path[n];
				room_name = get_room_name(info, info->ant[a].path[n], room_tab);
				ft_printf("L%d-%s ", info->ant[a].id, room_name);
			}
			a++;
			i++;
		}
		n++; // that level of the path is now full, let's look further.
		ft_putchar('\n');
	}
}
