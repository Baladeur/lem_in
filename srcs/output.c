/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 10:17:05 by myener            #+#    #+#             */
/*   Updated: 2020/03/03 14:51:30 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		lem_in_map_free_error(char **map)
{
	map ? tab_free(map) : 0;
	return (lem_in_error_output());
}

int		lem_in_error_output(void)
{
	ft_putendl("ERROR");
	return (0);
}
