/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:44:24 by tferrieu          #+#    #+#             */
/*   Updated: 2019/12/03 19:04:12 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	Returns the id of the room which's name matches the one given or -1 if no
**	such room exist.
*/

int	find_room(t_room *farm, char *name, t_info *info)
{
	int i;

	i = 0;
	while (i < info->room_nb)
	{
		if (!(ft_strcmp(farm[i].name, name)))
			return (i);
		i++;
	}
	return (-1);
}
