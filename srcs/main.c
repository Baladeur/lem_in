/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:40:33 by myener            #+#    #+#             */
/*   Updated: 2020/03/09 14:11:15 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int			is_room(char *line)
{
	int		i;

	i = 0;
	if (line[0] == '#')
		return (0);
	while (line[i] && line[i] != ' ' && line[i] != '-')
		i++;
	if (line[i] == ' ')
		return (1);
	return (0);
}

static int	room_counter(char **map)
{
	int i;
	int	room_nb;

	i = 0;
	room_nb = 0;
	while (map[i])
	{
		if (is_room(map[i]) == 1)
			room_nb++;
		i++;
	}
	return (room_nb);
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

static char	**get_map()
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

int			main()
{
	t_info	info;
	char	**map;
	t_path	*path_tab;

	map = NULL;
	if (!(map = get_map()))
		return (lem_in_error_output());
	info_init(&info);
	if ((info.ant_nb = ft_atoi(map[0])) <= 0)
		return (lem_in_map_free_error(map));
	if (!(info.ant = malloc(sizeof(t_ant) * info.ant_nb)))
		return (0);
	ant_init(&info);
	info.room_nb = room_counter(map);
	if (!(info.room_tab = malloc(sizeof(t_room) * info.room_nb)))
		return (0);
	if (!lem_in_parser(map, &info))
		return (lem_in_map_free_error(map));
	if (troubleshooter(&info) || !(adj_matrix(map, &info))
		|| !(directed_matrix(&info)) || !(pathfinder(&info, &path_tab)))
		return (lem_in_map_free_error(map));
	assign_path(path_tab, &info);
	lem_in_displayer(&info, map);
	map ? tab_free(map) : 0;
	room_free(&info);
	matrix_free(&(info.matrix), info.room_nb);
	matrix_free(&(info.dir_matrix), info.room_nb);
	path_free(&path_tab, 1);
	free(info.ant);
	return (0);
}
