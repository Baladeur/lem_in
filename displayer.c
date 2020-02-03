/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:40:45 by myener            #+#    #+#             */
/*   Updated: 2020/02/03 17:59:11 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	lem_in_displayer(t_info *info, t_path *path_tab, char **map)
{
	int		i;

	i = 0;
	printf("_____________\n\n"); // debug
	printf("DEBUT OUTPUT:\n\n"); // debug
	while (map[i]) // first we display the given map.
	{
		ft_putstr(map[i]);
		i++;
	}
	ft_putchar('\n'); // one additional space (needed in the examples)
	lem_in_dispatcher(info, path_tab);
	printf("FIN OUTPUT\n"); // debug
	printf("_____________\n\n"); // debug
}
