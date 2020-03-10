/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:40:33 by myener            #+#    #+#             */
/*   Updated: 2020/03/10 16:05:10 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int			is_room(char *line)
{
	int		i;

	i = 0;
	if (line[0] == '#')
		return (-1);
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] == ' ')
		return (1);
	return (0);
}

static char	**append_return(char **in)
{
	int		i;

	i = 0;
	while (in[i])
	{
		in[i] = ft_free_join(in[i], "\n");
		i++;
	}
	if (i == 0)
	{
		in ? tab_free(in) : 0;
		exit(0);
	}
	return (in);
}

static char	**get_map(void)
{
	int		i;
	char	*line;
	char	**map;
	t_elist	*stock;

	stock = NULL;
	map = NULL;
	line = NULL;
	while (get_next_line(0, &line))
		elist_add(&stock, (int *)line);
	if (!(map = (char **)malloc(sizeof(char *) * (elist_size(stock) + 1))))
		return (NULL);
	i = 0;
	while (stock)
	{
		map[i] = (char *)stock->edges;
		elist_delone(&stock, 0);
		i++;
	}
	map[i] = NULL;
	map = append_return(map);
	return (map);
}

int			main(void)
{
	t_info	info;
	char	**map;
	t_path	*path_tab;

	map = NULL;
	path_tab = NULL;
	if (!(map = get_map()))
		return (lem_in_error_output());
	if (!(lem_init(&info, map)))
		return (lem_in_free(map, &info, &path_tab, 0));
	if (!lem_in_parser(map, &info))
		return (lem_in_free(map, &info, &path_tab, 0));
	if (troubleshooter(&info) || !(adj_matrix(map, &info))
		|| !(directed_matrix(&info)) || !(pathfinder(&info, &path_tab)))
		return (lem_in_free(map, &info, &path_tab, 0));
	assign_path(path_tab, &info);
	lem_in_displayer(&info, map);
	return (lem_in_free(map, &info, &path_tab, 1));
}
