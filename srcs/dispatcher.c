/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:22:11 by myener            #+#    #+#             */
/*   Updated: 2020/03/03 14:44:30 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

char			*get_room_name(t_info *info, int room_id)
{
	int	i;

	i = 0;
	while (i < info->room_nb)
	{
		if (room_id == info->room_tab[i].id)
			return (info->room_tab[i].name);
		i++;
	}
	return (NULL);
}

static int		room_is_empty(t_info *info, int room_id)
{
	int	i;

	i = -1;
	while (++i < info->ant_nb)
		if (info->ant[i].pos == room_id)
			return (0);
	return (1);
}

static int		is_end_room(t_info *info, int room_id)
{
	int i;

	i = 0;
	while (i < info->room_nb)
	{
		if (info->room_tab[i].type == 'e')
			break ;
		i++;
	}
	if (room_id == info->room_tab[i].id)
		return (1);
	return (0);
}

void			lem_in_dispatcher(t_info *info, t_ant *ant)
{
	int		a;
	char	*room_name;

	a = 0;
	room_name = NULL;
	while (!is_end_room(info, info->ant[info->ant_nb - 1].pos))
	{
		a = 0;
		while (a < info->ant_nb)
		{
			if ((room_is_empty(info, ant[a].path[ant[a].i + 1])
				|| is_end_room(info, ant[a].path[ant[a].i + 1]))
				&& !is_end_room(info, ant[a].pos))
			{
				ant[a].i++;
				ant[a].pos = ant[a].path[ant[a].i];
				room_name = get_room_name(info, ant[a].path[ant[a].i]);
				room_name ? ft_printf("L%d-%s ", ant[a].id, room_name) : 0;
			}
			a++;
		}
		ft_putchar('\n');
	}
}

void			lem_in_displayer(t_info *info, char **map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		ft_putstr(map[i]);
		i++;
	}
	ft_putchar('\n');
	lem_in_dispatcher(info, info->ant);
}
