/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:40:33 by myener            #+#    #+#             */
/*   Updated: 2019/12/09 16:43:37 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


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
		in ? tab_free(in) : 0;
		exit(0);
	}
	return (in);
}

char		**get_map(char **av, char **map) // get map from standard input using GNL.
{
	int		i;
    int     fd;
	char	*tmp;
	char	*line;
	char	*stock;

	i = 0;
    fd = open((av[1]), O_RDONLY);
	stock = ft_strnew(1);
	while (get_next_line(fd, &line))
	{
		tmp = line;
		stock = ft_free_join(stock, line);
		stock = ft_free_join(stock, "\n");
		free(tmp);
		i++;
	}
	i = 0;
	while (stock[i])
	{
		(stock[i] == '\n' && stock[i + 1] == '\n') ? ft_putendl("ERROR") : 0;
		i++;
	}
	map = ft_strsplit(stock, '\n');
	map = append_return(map);
	ft_strdel(&stock);
	return (map);
}

int     main(int ac, char **av) // testing main for parsing
{
	int		i;
	t_info	info;
    char    **map;

    if (ac == 1) // if no args are given, return.
        return (0);
    map = NULL;
    map = get_map(av, map);
	info_init(&info);
	if ((info.ant_nb = ft_atoi(map[0])) <= 0) // if the number of ants is equal to 0 or negative, we stop.
		parsing_error(map);
	if (!(info.ant_position = malloc(sizeof(int) * info.ant_nb))) // malloc the int tab in which the ants and their position are stored
		return (0);
	ant_position_init(&info);
    info.room_nb = room_counter(map);
	if (!(info.room_tab = malloc(sizeof(t_room) * info.room_nb))) // malloc the array of struct in which the rooms and their data are stored
		return (0);
    lem_in_parser(map, &info);
	i = 0;
	while (i < info.ant_nb)
	{
		printf("ant = %d, position = %d\n", i + 1, info.ant_position[i]);
		i++;
	}
	i = 0;
	while (i < info.room_nb)
	{
		printf("id = %d, name = %s, x = %d, y = %d\n", info.room_tab[i].id, info.room_tab[i].name, info.room_tab[i].x, info.room_tab[i].y);
		i++;
	}
	free(info.ant_position);
	free_struct_array(&info);
	free(info.room_tab);
    return (0);
}
