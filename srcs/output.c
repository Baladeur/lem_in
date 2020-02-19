/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 10:17:05 by myener            #+#    #+#             */
/*   Updated: 2020/02/19 17:40:09 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int				lem_in_map_free_error(char **map) // segmented for debugging purposes, to be integrated to a larger function later.
{
	map? tab_free(map) : 0;
	return (lem_in_error_output());
}

int		lem_in_error_output(void)
{
	ft_putendl("ERROR");
	return (0);
}

// void			display_int_tab(int *tab, int len) // debug only
// {
// 	int	i;

// 	i = 0;

// 	printf("START:\n");
// 	while (i < len)
// 	{
// 		printf("%d\n", tab[i]);
// 		i++;
// 	}
// 	printf("END\n");
// }

// void			display_rooms(t_room *room_tab, int len) // debug only
// {
// 	int	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		printf("id = %d, name = %s\n", room_tab[i].id, room_tab[i].name);
// 		i++;
// 	}
// }
