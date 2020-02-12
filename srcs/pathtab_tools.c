/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathtab_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:36:05 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/12 20:57:46 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

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
** Returns the number of instructions it would
** take for n ants to go through pathtab.
*/

int		pathtab_efficiency(t_path *pathtab, int n)
{
	int longest;
	int remain;
	int i;

	i = 0;
	longest = pathtab[0].len;
	while (pathtab[++i].len > 0)
		if (pathtab[i].len > longest)
			longest = pathtab[i].len;
	remain = n;
	i = -1;
	while (pathtab[++i].len > 0)
		remain -= longest - pathtab[i].len;
	return (remain / i + longest - 1 + (remain % i ? 1 : 0));
}

/*
** Frees an allocated t_path tab.
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
** Adds a set of edges to a t_path tab. Returns 1 if the operation is successful,
** 0 if the set is incompatible with the other sets already included in the pathtab.
*/

int		pathtab_add(t_path *pathtab, int *edges, t_info *info, int b)
{
	int i;
	int s;
	int l;

	s = pathtab_size(pathtab);
	i = 0;
	l = 2;
	while (edges[++i] != info->room_nb - 1)
		if ((++l) && pathtab[s].edges[edges[i]] && !b)
			return (0);
	i = -1;
	while (pathtab[++i].len > 0)
		;
	pathtab[i].len = i;
	pathtab[i].edges = edges;
	i = 0;
	if (!b)
		while (edges[++i] != info->room_nb - 1)
			pathtab[s].edges[edges[i]] = 1;
	return (1);
}
