/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 15:32:18 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/19 15:27:27 by tferrieu         ###   ########.fr       */
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

t_paths	*destroy_paths(t_paths **paths)
{
	t_paths *current;
	t_paths *tmp;

	if (!paths || !(*paths))
		return (NULL);
	current = *paths;
	*paths = NULL;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
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

t_paths	*new_paths(t_path *path, int count)
{
	t_paths	*paths;
	int		i;

	if (count < 2 || !path || !(paths = (t_paths *)malloc(sizeof(t_paths))))
		return (NULL);
	paths->count = NULL;
	paths->next = NULL;
	paths->path = path;
	if (!(paths->nodes = (int *)malloc(sizeof(int) * count)))
		return (destroy_paths(&paths));
	if (!(paths->count = (int *)malloc(sizeof(int))))
		return (destroy_paths(&paths));
	i = -1;
	while (++i < count)
		paths->nodes[i] = path->nodes[i];
	paths->count[0] = 1;
	return (paths);
}

t_paths	*add_path(t_paths *paths, t_path *path, int count)
{
	t_paths	*new;
	int		i;

	if (!path || !paths || !(new = (t_paths *)malloc(sizeof(t_paths))))
		return (NULL);
	new->nodes = paths->nodes;
	new->count = paths->count;
	new->count[0]++;
	new->path = path;
	new->next = NULL;
	i = -1;
	while (++i < count)
		if (path->nodes[i])
			new->nodes[i] = 1;
	paths->next = new;
	return (paths);
}
