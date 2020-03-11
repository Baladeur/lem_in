/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 21:04:26 by tferrieu          #+#    #+#             */
/*   Updated: 2020/03/11 15:27:40 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

/*
** Sets the path each ant will use once pathfinding is done.
*/

void		assign_path(t_path *path, t_info *info)
{
	int l;
	int r;
	int	s;
	int i[4];

	i[0] = 0;
	l = path[0].len;
	while (path[++i[0]].len > 0)
		if (path[i[0]].len > l)
			l = path[i[0]].len;
	r = info->ant_nb;
	i[0] = -1;
	while (path[++i[0]].len > 0)
		r -= l - path[i[0]].len;
	s = r / i[0];
	r = r % i[0];
	i[1] = -1;
	i[2] = 0;
	while (path[++i[1]].len > 0 && (i[3] = -1))
		while (++i[3] < s + l - path[i[1]].len + (i[0] - i[1] <= r ? 1 : 0))
		{
			info->ant[i[2]].path = path[i[1]].edges;
			i[2]++;
		}
}

static int	strnumcheck(char *str, int nb)
{
	int i;
	int c1;
	int c2;

	i = str[0] == '-' || str[0] == '+' ? 1 : 0;
	c1 = 0;
	c2 = 0;
	while (str[i] == '0')
		i++;
	while (ft_isalnum(str[i]) && ++i)
		c1++;
	while (nb != 0 && ++c2)
		nb /= 10;
	return (c1 != c2);
}

/*
** atoi for lem_in. st is the start index of the numer in str
** ret is the result of the conversion. Returns 0 if an error was met.
*/

int			lem_in_atoi(char *str, int st, int len, int *ret)
{
	char	*nb;
	int		i;

	if (!(nb = ft_strsub(str, st, len)))
		return (0);
	i = 1;
	*ret = ft_atoi(nb);
	if ((strnumcheck(nb, *ret)))
		i = 0;
	free(nb);
	return (i);
}
