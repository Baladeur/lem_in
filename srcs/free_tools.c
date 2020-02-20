/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:59:26 by myener            #+#    #+#             */
/*   Updated: 2020/02/20 21:35:26 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

void	ant_free(t_info *info)
{
	int i;

	i = 0;
	while (i < info->ant_nb)
	{
		// free(info->ant[i].path);
		i++;
	}
	// info->ant ? free(info->ant) : 0;
}

/*
**	Free the memory of an int** where every allocated int* is found before the
**	first NULL int*. Will leak if there is a NULL int* in-between the allocated
**	int*
*/

int		**matrix_free(int ***matrix, int count)
{
	int i;

	i = -1;
	while (++i < count)
		free(**matrix + i);
	free(*matrix);
	*matrix = NULL;
	return (NULL);
}


/*
** Frees an allocated t_path tab.
*/

t_path	*pathtab_free(t_path **pathtab, int b)
{
	int	i;

	if (!pathtab || *pathtab)
		return (NULL);
	i = -1;
	while (b && pathtab[0][++i].len > 0)
		if (pathtab[0][i].edges)
			free(pathtab[0][i].edges);
	free(pathtab[0]);
	pathtab[0] = NULL;
	return (NULL);
}

void	room_free(t_info *info)
{
	int i;

	i = 0;
	while (i < info->room_nb)
	{
		// free(info->room_tab[i].name);
		i++;
	}
	// info->room_tab ? free(info->room_tab) : 0;
}
