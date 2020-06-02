/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:04:26 by tferrieu          #+#    #+#             */
/*   Updated: 2020/06/02 18:47:55 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** An atoi for lem_in. ret is the result of the conversion.
** Returns 0 if an error was met.
*/

int	lem_in_free(char **map, t_info *info, t_path **path, int b)
{
	map ? tab_free(map) : 0;
	info->ant ? free(info->ant) : 0;
	info->room_tab ? room_free(info) : 0;
	info->matrix ? matrix_free(&(info->matrix), info->room_nb) : 0;
	path_free(path, 1);
	return (b ? 0 : lem_in_error_output());
}

int	lem_in_error_output(void)
{
	ft_putendl("ERROR");
	return (0);
}

int	lem_in_atoi(char *str, int *ret)
{
	int i;
	int nb;
	int c1;
	int c2;

	*ret = ft_atoi(str);
	nb = *ret;
	i = str[0] == '-' || str[0] == '+' ? 1 : 0;
	c1 = 0;
	c2 = 0;
	while (str[i] == '0')
		i++;
	while (str[i] && str[i] != '\n' && ++i)
		c1++;
	while (nb != 0 && ++c2)
		nb /= 10;
	return (c1 == c2);
}
