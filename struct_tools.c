/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:58:11 by myener            #+#    #+#             */
/*   Updated: 2019/12/08 21:20:28 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	info_init(t_info *info)
{
	info->room_nb = 0;
	info->start_nb = 0;
	info->end_nb = 0;
	info->ant_nb = 0;
	info->ant_position = 0;
	info->room_tab = NULL;
	info->matrix = NULL;
}

void	free_struct_array(t_info *info)
{
	int i;

	i = 0;
	while (i < info->room_nb)
	{
		free(info->room_tab[i].name);
		i++;
	}
}

void	room_init(t_room *room)
{
	room->id = 0;
	room->name = NULL;
	room->x = 0;
	room->y = 0;
	room->type = 'c'; // default room type is classic
	room->ant_nb_curr = 0;
}
