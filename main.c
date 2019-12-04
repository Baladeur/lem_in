/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:40:33 by myener            #+#    #+#             */
/*   Updated: 2019/12/04 16:23:51 by myener           ###   ########.fr       */
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

char		**get_data(char **av, char **data) // get data from standard input using GNL.
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
	data = ft_strsplit(stock, '\n');
	data = append_return(data);
	ft_strdel(&stock);
	return (data);
}

int     main(int ac, char **av) // testing main for parsing
{
    // int     i;
    t_room  *room;
    t_ant   ant;
    t_ant   *ant_prt;
    char    **data;

    if (ac == 1)
        return (0);
    room = NULL;
    data = NULL;
    data = get_data(av, data);
    // i = 0;
    // while (data[i])
    // {
    //     printf("data[%d] = '%s'\n", i, data[i]);
    //     i++;
    // }
    lem_in_parser(data, room, &ant);
    // while (room)
    // {
    //     printf("room name = %s & room id = %d\n", room->name, room->id);
    //     room = room->next;
    // }
    ant_prt = &ant;
    while (ant_prt)
    {
        printf("ant number = %d & ant position = %d\n", ant_prt->id, ant_prt->position);
        ant_prt = ant_prt->next;
    }
    return (0);
}

// int     main(int argc, char **argv)
// {
//     t_room  *room;
//     t_ant   *ant;
//     char    **data;

//     room = NULL;
//     data = get_data(data);
//     lem_in_parser(data, room, ant);
//     return (0);
// }