/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:40:45 by myener            #+#    #+#             */
/*   Updated: 2020/01/21 18:02:15 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	displayer(t_paths *path, t_info *info, char **map)
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
	i = 1; // i starts at 1 cause the ants id's start at 1.
	ant_last_pos = 0; // at first, all ants start at 0
	while (i < info->ant_nb) // while we go through all the ants
	{

		if (info->ant_position[i] != ant_last_pos) // if the ant position is now different
		ft_printf("L%d-%s ", /*ant_number*/, /*room_name*/);
	}
	ft_putchar('\n'); // go to next line for the next iteration
}
