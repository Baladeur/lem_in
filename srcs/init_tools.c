/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:58:11 by myener            #+#    #+#             */
/*   Updated: 2020/03/10 15:56:38 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		lem_init(t_info *info, char **map)
{
	int	i;

	info_init(info);
	i = 0;
	while (map[i] && is_room(map[i]) < 0)
		i++;
	if ((info->ant_nb = ft_atoi(map[i])) <= 0
		|| !(info->ant = malloc(sizeof(t_ant) * info->ant_nb)))
		return (0);
	ant_init(info);
	while (map[++i] && is_room(map[i]))
		if (is_room(map[i]) == 1)
			info->room_nb++;
	if (!(info->room_tab = malloc(sizeof(t_room) * info->room_nb)))
		return (0);
	return (1);
}

void	ant_init(t_info *info)
{
	int i;

	i = 0;
	while (i < info->ant_nb)
	{
		info->ant[i].id = i + 1;
		info->ant[i].i = 0;
		info->ant[i].pos = 0;
		info->ant[i].path = NULL;
		i++;
	}
}

void	info_init(t_info *info)
{
	info->room_nb = 0;
	info->start_nb = 0;
	info->end_nb = 0;
	info->ant_nb = 0;
	info->s_enc = 0;
	info->e_enc = 0;
	info->ant = NULL;
	info->path_nb = 0;
	info->edges_line = 0;
	info->room_tab = NULL;
	info->matrix = NULL;
	info->dir_matrix = NULL;
}

void	room_init(t_room *room)
{
	room->id = 0;
	room->name = NULL;
	room->x = 0;
	room->y = 0;
	room->type = 'c';
	room->ant_nb_curr = 0;
}
