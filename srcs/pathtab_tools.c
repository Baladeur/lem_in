/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathtab_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:36:05 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/10 23:04:33 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Frees an allocated t_path tab of size 's'.
*/

t_path	*pathtab_destroy(t_path **pathtab)
{
	int	i;

	if (!pathtab || *pathtab)
		return (NULL);
	i = -1;
	while (pathtab[0][++i].len > 0)
		if (pathtab[0][i].edges)
			free(pathtab[0][i].edges);
	free(pathtab[0]);
	pathtab[0] = NULL;
	return (NULL);
}

/*
** Initialize a t_path tab of size 's'.
*/

t_path	*pathtab_init(int s, t_info *info)
{
	t_path	*pathtab;
	int 	i;

	if (!(pathtab = (t_path *)malloc(sizeof(t_path) * (s + 1))))
		return (NULL);
	i = -1;
	while (++i <= s)
	{
		pathtab[i].edges = NULL;
		pathtab[i].len = i == s ? -1 : 0;
	}
	if (!(pathtab[s].edges = (int *)malloc(sizeof(int) * info->room_nb)))
		return (pathtab_destroy(&pathtab));
	i = -1;
	while (++i < info->room_nb)
		pathtab[s].edges = 0;
	return (pathtab);
}

/*
** Returns the size of a t_path tab.
*/

int		pathtab_size(t_path *pathtab)
{
	int		i;

	i = 0;
	while (pathtab[i].len >= 0)
		i++;
	return (i);
}

/*
** Adds a set of edges to a t_path tab. Returns 1 if the operation is successful,
** 0 if the set is incompatible with the other sets already included in the pathtab.
*/

int		pathtab_add(t_path *pathtab, int *edges, t_info *info)
{
	int i;
	int s;
	int l;

	s = pathtab_size(pathtab);
	i = -1;
	l = 0;
	while (edges[++i] != info->room_nb - 1)
		if ((++l) && pathtab[s].edges[edges[i]])
			return (0);
	i = -1;
	while (pathtab[++i].len > 0)
		;
	pathtab[i].len = i;
	pathtab[i].edges = edges;
	i = -1;
	while (edges[++i] != info->room_nb - 1)
		pathtab[s].edges[edges[i]] = 1;
	return (1);
}
