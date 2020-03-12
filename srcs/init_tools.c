/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:58:11 by myener            #+#    #+#             */
/*   Updated: 2020/03/12 15:16:29 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static void	ant_init(t_info *info)
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

static void	info_init(t_info *info)
{
	info->room_nb = 0;
	info->start_nb = 0;
	info->end_nb = 0;
	info->ant_nb = 0;
	info->s_enc = 0;
	info->e_enc = 0;
	info->ant = NULL;
	info->path_nb = 0;
	info->edges_line = MAX_INT;
	info->rooms_line = 1;
	info->room_tab = NULL;
	info->matrix = NULL;
	info->dir_matrix = NULL;
}

static void	room_init(t_room *room)
{
	room->id = 0;
	room->name = NULL;
	room->x = 0;
	room->y = 0;
	room->type = 'c';
	room->ant_nb_curr = 0;
}

int			lem_init(t_info *info, char **map)
{
	int	i;
	int	res;

	info_init(info);
	i = 0;
	while (map[i] && is_room(map[i]) < 0)
		i++;
	if (!(lem_in_atoi(map[i], &info->ant_nb)) || info->ant_nb < 1
		|| !(info->ant = malloc(sizeof(t_ant) * info->ant_nb)))
		return (0);
	ant_init(info);
	info->rooms_line = i;
	while (map[++i] && (res = is_room(map[i])))
		if (res == 1)
			info->room_nb++;
	if (!(info->room_tab = malloc(sizeof(t_room) * info->room_nb)))
		return (0);
	i = -1;
	while (++i < info->room_nb)
		room_init(&info->room_tab[i]);
	return (1);
}

/*
** Initialize a t_path tab of size 's'.
*/

t_path		*path_init(int s, t_info *info)
{
	t_path	*path;
	int		i;

	if (!(path = (t_path *)malloc(sizeof(t_path) * (s + 1))))
		return (NULL);
	i = -1;
	while (++i < s && !(path[i].edges = NULL))
		path[i].len = 0;
	path[s].len = -1;
	if (!(path[s].edges = (int *)malloc(sizeof(int) * info->room_nb)))
		return (path_free(&path, 0));
	i = -1;
	while (++i < info->room_nb)
		path[s].edges[i] = i == 0 || i == info->room_nb - 1 ? 1 : 0;
	return (path);
}
