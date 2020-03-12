/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:22:11 by myener            #+#    #+#             */
/*   Updated: 2020/03/12 19:21:26 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static char		*get_room(t_info *info, int room_id)
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

static void		lem_in_printer(int id, char *name)
{
	ft_putchar('L');
	ft_putnbr(id);
	ft_putchar('-');
	ft_putstr(name);
	ft_putchar(' ');
}

void			lem_in_displayer(t_info *info, char **map)
{
	int		a;
	char	*room_name;

	display_map(map);
	a = 0;
	room_name = NULL;
	while (!is_end_room(info, info->ant[info->ant_nb - 1].pos))
	{
		a = -1;
		while (++a < info->ant_nb)
		{
			if (!is_end_room(info, info->ant[a].pos) &&
				(room_is_empty(info, info->ant[a].path[info->ant[a].i + 1])
				|| is_end_room(info, info->ant[a].path[info->ant[a].i + 1])))
			{
				info->ant[a].i++;
				info->ant[a].pos = info->ant[a].path[info->ant[a].i];
				room_name = get_room(info, info->ant[a].path[info->ant[a].i]);
				room_name ? lem_in_printer(info->ant[a].id, room_name) : 0;
			}
		}
		ft_putchar('\n');
	}
}
