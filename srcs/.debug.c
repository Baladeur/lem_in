/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .debug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:46:01 by myener            #+#    #+#             */
/*   Updated: 2020/02/11 16:46:49 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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