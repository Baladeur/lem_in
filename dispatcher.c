/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:22:11 by myener            #+#    #+#             */
/*   Updated: 2020/01/22 16:05:48 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	dispatcher(t_info *info, t_path *path_tab, t_room *room_tab)
{
	int		a;	// current ant
	int		i;	// index
	int		n;	// path_tab index
	char	*room_name;

	i = 0;
	a = 1;	// as stipulated in the subject, ant IDs start at 1.
	n = 1;	// 1 and not 0 because path_tab[i].edges[0] = the start room
	room_name = NULL;
	while (path_tab[i].len != -1)
	{
		if (room_is_empty(path_tab[i].edges[n])) // goes thru ant arr. to see if an ant's here
		{
			info->ant[a].id = path_tab[i].edges[n];
			room_name = get_room_from_id(path_tab[i].edges[n], room_tab);
			ft_printf("L%d-%s ", a, room_name);
			a++;
			n++;
		}
		i++;
	}
}
