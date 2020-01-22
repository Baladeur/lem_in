/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:40:45 by myener            #+#    #+#             */
/*   Updated: 2020/01/22 16:06:37 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	displayer(t_info *info, t_path *path_tab, t_room *room_tab, char **map)
{
	int		i;
	int		ant_last_pos; // the last position of the current ant (before this iteration).

	i = 0;
	while (map[i]) // first we display the given map.
	{
		ft_putstr(map[i]);
		i++;
	}
	ft_putchar('\n'); // one additional space (needed in the examples)
	dispatcher(info, path_tab, room_tab);
}
