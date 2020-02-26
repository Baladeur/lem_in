/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:40:33 by myener            #+#    #+#             */
/*   Updated: 2020/02/26 16:56:35 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

int				is_room(char *line)
{
	int 	i;

	i = 0; // first let's start by checking whether it's a room or path.
	if (line[0] == '#')
		return (0);
	while (line[i] && line[i] != ' ' && line[i] != '-') // let's parse the first element of the string.
		i++;
	if (line[i] == ' ') // if the next element is a space, then it's a room
		return (1);
	return (0); // else it's an error.
}

static int		room_counter(char **map)
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

char		**append_return(char **in)
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
		// in ? tab_free(in) : 0;
		exit(0);
	}
	return (in);
}

char		**get_map(char **av, char **map) // get map from standard input using GNL.
{
	int		nb;
	int		i;
	int		fd;
	char	*line;
	t_elist	*stock;

	if ((fd = open((av[1]), O_RDONLY)) < 0)
		return (NULL);
	stock = NULL;
	map = NULL;
	line = NULL;
	while (get_next_line(fd, &line))
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

// void	path_tab_init(t_path *path_tab, t_info *info) // debug only - for testing with map_1.
// {
// 	int i;
// 	int	j;

// 	path_tab[0].len = 4; // 4 for map_1 & map_1_2 ; 5 for map_2.
// 	if (!(path_tab[0].edges = malloc(sizeof(int) * path_tab[0].len)))
// 		return ;
// 	path_tab[0].edges[0] = 0;
// 	path_tab[0].edges[1] = 1;
// 	path_tab[0].edges[2] = 2;
// 	path_tab[0].edges[3] = 3;
// 	i = 0;
// 	j = 0;
// 	while (i < info->ant_nb)
// 	{
// 		info->ant[i].path = path_tab[0].edges;
// 		i++;
// 	}

// }

int     	main(int ac, char **av) // testing main for parsing
{
	int		i;
	int		j;
	t_info	info;
    char    **map;
	t_path	*path_tab; // debug; fake path_tab object created for testing.

    if (ac == 1) // if no args are given, return.
        return (0);
    map = NULL;
    if (!(map = get_map(av, map))) // if no map is given, display "ERROR" and return.
		return (lem_in_error_output());
	info_init(&info);
	if ((info.ant_nb = ft_atoi(map[0])) <= 0) // if the number of ants is equal to 0 or negative, we stop, display "ERROR" and return.
		return (lem_in_map_free_error(map));
	if (!(info.ant = malloc(sizeof(t_ant) * info.ant_nb))) // malloc the structure array in which the ants and their position are stored
		return (0);
	ant_init(&info); // initialize the ants according to their numbers. all initial positions should point to 0 aka start room's id.
	// path_tab_init(&path_tab, &info); // debug; fake path_tab initializer & filler for testing.
    info.room_nb = room_counter(map);
	if (!(info.room_tab = malloc(sizeof(t_room) * info.room_nb))) // malloc the array of struct in which the rooms and their data are stored
		return (0);
    lem_in_parser(map, &info); // parse the map data and stock it accordingly.
	if (troubleshooter(&info))
		return (lem_in_map_free_error(map));
	if (!(adj_matrix(map, &info)))	// creates the adjacency matrix
		return (lem_in_map_free_error(map));
	if (!(directed_matrix(&info)))	// creates the directed matrix
		return (lem_in_map_free_error(map));
	if (!(pathfinder(&info, &path_tab)))	// stores the best t_path tab in path_tab
		return (lem_in_map_free_error(map));
	ft_printf("Efficiency : %d\n", path_efficiency(path_tab, info.ant_nb));
	i = -1;
	while (path_tab[++i].len > 0 && (j = -1))
	{
		ft_printf("%d |\t", i);
		while (path_tab[i].edges[++j] != info.room_nb - 1)
			ft_printf("%s ", info.room_tab[path_tab[i].edges[j]].name);
		ft_printf("%s\n", info.room_tab[path_tab[i].edges[j]].name);
	}
	// return (0);
	assign_path(path_tab, &info);
	// i = 0; // debug
	// while (i < info.ant_nb) // debug
	// {
	// 	printf("ant = %d, position = %d\n", i + 1, info.ant[i].pos);
	// 	i++;
	// }
	// i = 0; // debug
	// while (i < info.room_nb)
	// {
	// 	printf("id = %d, name = %s, x = %d, y = %d\n", info.room_tab[i].id, info.room_tab[i].name, info.room_tab[i].x, info.room_tab[i].y);
	// 	i++;
	// } // debug
	// i = 0; // debug
	// printf("\nPATH(S):\n* "); // debug
	// while (i < path_tab.len - 1) // debug
	// {
	// 	printf("%s, ", get_room_name(&info, path_tab.edges[i]));
	// 	i++;
	// } // debug
	// printf("%s.\n", get_room_name(&info, path_tab.edges[i]));
	// ft_putchar('\n');
	// i = 0;
	// while (i < info.ant_nb) // debug for as long as we dont have assigned paths to ants
	// {
	// 	info.ant[i].path = path_tab[0].edges;
	// 	i++;
	// }
	lem_in_displayer(&info, map);
	// map ? tab_free(map) : 0;
	ant_free(&info);
	room_free(&info);
    return (0);
}
