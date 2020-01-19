/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:38:58 by tferrieu          #+#    #+#             */
/*   Updated: 2020/01/19 15:23:13 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	print_paths(t_paths *paths, int count)
{
	t_paths *current;
	int		i;

	ft_printf("Number of paths : %d | Ensemble nodes : [", paths->count[0]);
	i = -1;
	while (++i < count)
		if (i < count - 1)
			ft_printf("%d, ", paths->nodes[i]);
		else
			ft_printf("%d]\n{\n", paths->nodes[i]);
	current = paths;
	while (current)
	{
		ft_printf("\t");
		print_path(current->path, count);
		current = current->next;
	}
	ft_printf("}\n");
}
