/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 10:17:05 by myener            #+#    #+#             */
/*   Updated: 2020/03/10 16:24:54 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int		lem_in_free(char **map, t_info *info, t_path **path, int b)
{
	map ? tab_free(map) : 0;
	info->ant ? free(info->ant) : 0;
	info->room_tab ? room_free(info) : 0;
	info->matrix ? matrix_free(&(info->matrix), info->room_nb) : 0;
	info->dir_matrix ? matrix_free(&(info->dir_matrix), info->room_nb) : 0;
	path_free(path, 1);
	return (b ? 0 : lem_in_error_output());
}

int		lem_in_error_output(void)
{
	ft_putendl("ERROR");
	return (0);
}
