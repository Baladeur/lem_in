/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:32:18 by tferrieu          #+#    #+#             */
/*   Updated: 2019/11/29 15:32:19 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path			*destroy_path(t_path **path)
{
	if ((*path)->nodes)
		free((*path)->nodes);
	if ((*path)->edges)
		free((*path)->edges);
	free(*path);
	*path = NULL;
	return (NULL);
}

t_path			*new_path(int *edges, int count)
{
	t_path	*path;
	int		i;

	if (edges == NULL || !(path = (t_path *)malloc(sizeof(t_path))))
		return (NULL);
	path->edges = edges;
	path->nodes = NULL;
	if (!(path->nodes = (int *)malloc(sizeof(int) * count)))
		return (destroy_path(&path));
	i = -1;
	while (++i < count)
		path->nodes[i] = 0;
	path->len = 0;
	i = -1;
	while (++i < count && edges[i] >= 0)
	{
		if (edges[i] >= count || path->nodes[edges[i]] != 0)
			return (destroy_path(&path));
		path->nodes[edges[i]] = 1;
		path->len++;
	}
	return (path);
}

void			print_path(t_path *path, int count)
{
	int i;

	if (!path)
	{
		ft_printf("Error\n");
		return ;
	}
	ft_printf("Edges |");
	i = -1;
	while (++i < count && path->edges[i] >= 0)
		ft_printf(" %d", path->edges[i]);
	ft_printf("\nNodes |");
	i = -1;
	while (++i < count)
		ft_printf(" %d", path->nodes[i]);
	ft_printf("\n\nPath length :\t%d\n", path->len);
}
