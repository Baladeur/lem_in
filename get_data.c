/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:24 by myener            #+#    #+#             */
/*   Updated: 2019/12/03 13:48:55 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		parsing_error(char **data)
{
	tab_free(data);
	ft_putendl("ERROR");
	return (0);
}

void	room_parser(char *line, t_room *room_list)
{
	int	i;
	int	start;

	i = 0;
	while(room_list && room_list->name) // goes to the last element of the list, if it's not the first node.
		room_list = room_list->next;
	room_list = room_node_malloc(room_list); // malloc and initializes the new node.
	while (line[i] && line[i] != ' ') // let's grab the first element of the string (room name).
		i++;
	room_list->id = room_list->prev ? room_list->prev->id + 1 : 1;
	room_list->name = ft_strsub(line, 0, i);
	i++; // jumps over the ' '
	start = i;
	while (line[i] && line[i] != ' ') // let's grab the second element of the string (coord x).
		i++;
	room_list->x = ft_atoi(ft_strsub(line, start, i));
	i++; // jumps over the ' '
	start = i;
	while (line[i] && line[i] != ' ') // let's grab the last element of the string (coord y).
		i++;
	room_list->y = ft_atoi(ft_strsub(line, start, i));
}

int		room_or_path(char *line)
{
	int 	i;

	i = 0; // first let's start by checking whether it's a room or path.
	while (/*line[i] (maybe useless) && */line[i] != ' ' && line[i] != '-') // let's parse the first element of the string.
		i++;
	if (line[i + 1] == ' ') // if the next element is a space, then it's a room
		return (1);
	else if (line[i + 1] == '-') // if it's a hyphen, then it's a path
		return (2);
	return (0); // else it's an error.
}

void	gates_manager(char **data, t_info *info, int ret, int i) // manages the gates' (start and end rooms) info.
{
	int		j;
	t_info	*info;

	i += 1; // go to the next line to fetch either start or end data.
	j = 0;
	if ((ret == 2 && info->s_enc) || (ret == 3 && info->e_enc)) // if this is the second start or end, error.
		parsing_error(data);
	if (info->s_enc = (ret == 2)) // if the command is "start", then the line contains the start room's data.
		info->start_nb = i; // marks the line of the start name and coordinates.
	else if (info->e_enc = (ret == 3))
		info->end_nb = i; // marks the line of the start name and coordinates.
}

int		hash_line_manager(char **data, int i) // does what is needed for lines starting with #.
{
	char	*command;

	if (!data[i][1]) // if the line was just one single '#', ignore.
		return (1);
	else if (data[i][1] != '#') // if the first line character is a # and not the next one, it's a comment, so move on.
		return (1);
	else if (data[i][1] == '#') // if there's another # after, then it might be a command.
	{
		if (data[i][2] == '#') // if the line start with "###", then it isn't well formatted, move on.
			return (1);
		else // else it might be a command : let's fetch it to see if it exists.
		{
			command = ft_strsub(data[i], 2, ft_strlen(data[i] - 2));
			if (!(ft_strcmp(command, "start")))
				return (2);
			else if (!(ft_strcmp(command, "end")))
				return (3);
			else // else the command doesn't exist, so move on.
				return (1);
		}
	}
	return (0);
}

void     parser(char **data, t_room *room_list) // parses the given data to get various info.
{
    int     i;
    int     j;
	int		ret;
	int		ant_nb;
	t_info	info;

	if ((ant_nb = ft_atoi(data[0])) <= 0) // if the number of ants is equal to 0 or negative, we stop.
		parsing_error(data);
	info.ant_nb = ant_nb;
    i = 1; // data[0] has already been treated above, now we can proceed to parse the rest.
    j = 0;
    while (data[i])
    {
		if (data[i][0] == 'L') // lines can't start with L. If they do, output error.
			parsing_error(data);
		else if (data[i][0] == '#') // if it starts with #, it might be a comment or a command:
		{
			ret = hash_line_manager(data, i); // this function will increment i to ignore the current line if necessary.
        	((ret == 2) || (ret == 3)) ? gates_manager(data, &info, ret, i) : 0; // if ret is 2 or 3, it means start or end was encountered
			i += (ret == 1) ? 1 : 2; // if it's a comment, we just ignore it, if it's a command we also ignore the next line, which has been recorded.
		}
		else if ((data[i][0] >= 33 && data[i][0] <= 126)) // if it starts with a letter, number or special character, it might be a room or a path:
		{
			if ((ret = room_or_path(data[i])) == 0) // if the format doesn't match a room or path, it' an error.
		   		parsing_error(data);
			(ret == 1) ? room_parser(data[i], room_list) : path_parser(data[i]); // if it's valid, parse accordingly.
		}
		i++;
    }
    return ;
}

char		**get_data(char **data) // get data from standard input using GNL.
{
	int		i;
	char	*tmp;
	char	*line;
	char	*stock;

	i = 0;
	stock = ft_strnew(1);
	while (get_next_line(0, &line))
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
