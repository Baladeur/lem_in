/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   troubleshooter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:15 by myener            #+#    #+#             */
/*   Updated: 2020/02/06 10:10:40 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		coord_double(t_room *tab, int nb)
{
	int		i;
	int		j;

	i = 0;
	while (i < nb)
	{
		j = 0;
		while (j < nb)
		{
			if (i != j && tab[i].x == tab[j].x && tab[i].y == tab[j].y )
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		name_double(t_room *tab, int nb)
{
	int		i;
	int		j;

	i = 0;
	while (i < nb)
	{
		j = 0;
		while (j < nb)
		{
			if (i != j && !ft_strcmp(tab[i].name, tab[j].name))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		troubleshooter(t_info *info)
{
	int		i;

	if (name_double(info->room_tab, info->room_nb)) // if we encounter the same room name twice
		return (1);
	if (coord_double(info->room_tab, info->room_nb)) // if two rooms have the same coordinates
		return (1);
	if (!info->room_tab[0].name || !info->room_tab[info->room_nb - 1].name) // if there is no start and/or end rooms
		return (1);
	i = 0;
	while (i < info->room_nb) // if coordinates have non-positive integers
	{
		if (i != 0 && info->room_tab[i].id == 0) // if an id isn't initialized
			return (1);
		if (!info->room_tab[i].name) // if a name isn't initialized
			return (1);
		if (info->room_tab[i].x < 0 || info->room_tab[i].y < 0)
			return (1);
		i++;
	}
	return (0);
}
