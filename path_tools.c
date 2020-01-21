/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:32:18 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/21 17:04:48 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*destroy_path(t_path **path)
{
	if (*path)
	{
		if ((*path)->nodes)
			free((*path)->nodes);
		if ((*path)->edges)
			free((*path)->edges);
		free(*path);
		*path = NULL;
	}
	return (NULL);
}

t_path	*new_path(int *edges, int count, int len)
{
	t_path	*path;
	int		i;

	path = NULL;
	if (!edges || count < 2 || len < 2 || !(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	path->edges = edges;
	path->nodes = NULL;
	path->len = len;
	if (!(path->nodes = (int *)malloc(sizeof(int) * count)))
		return (destroy_path(&path));
	i = -1;
	while (++i < count)
		path->nodes[i] = 0;
	i = -1;
	while (++i < len)
		if (edges[i] >= count || path->nodes[edges[i]] != 0)
			return (destroy_path(&path));
		else
			path->nodes[edges[i]] = 1;
	return (path);
}

void	print_path(t_path *path, int count)
{
	int i;

	ft_printf("Path size : %d | Path : {", path->len);
	i = -1;
	while (++i < path->len)
		if (i < path->len - 1)
			ft_printf("%d, ", path->edges[i]);
		else
			ft_printf("%d} | Nodes : [", path->edges[i]);
	i = -1;
	while (++i < count)
		if (i < count - 1)
			ft_printf("%d, ", path->nodes[i]);
		else
			ft_printf("%d]\n", path->nodes[i]);
}
