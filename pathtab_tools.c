/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathtab_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:36:05 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/05 00:18:49 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Frees an allocated t_path tab of size 's'.
*/

t_path	*pathtab_destroy(t_path **pathtab, int s)
{
	int i;

	if (!pathtab || *pathtab)
		return (NULL);
	i = -1;
	while (++i < s && pathtab[0][i].len > 0)
	{
		if (pathtab[0][i].nodes)
			free(pathtab[0][i].nodes);
		if (pathtab[0][i].edges)
			free(pathtab[0][i].edges);
	}
	free(pathtab[0]);
	pathtab[0] = NULL;
	return (NULL);
}

/*
** Initialize a t_path tab of size 's'.
*/

t_path	*pathtab_init(int s)
{
	t_path  *pathtab;

	if (!(pathtab = (t_path *)malloc(sizeof(t_path) * (s + 1))))
		return (NULL);
}

/*
** 
*/

int		*pathtab_capacity(t_path *pathtab, int s, t_info *info)
{
	int i;
	int total;
	int longest;
}
