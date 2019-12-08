/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:24 by myener            #+#    #+#             */
/*   Updated: 2019/12/08 21:05:23 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		parsing_error(char **map)
{
	tab_free(map);
	ft_putendl("ERROR");
	return (0);
}

int		room_or_path(char *line)
{
	int 	i;

	i = 0; // first let's start by checking whether it's a room or path.
	while (/*line[i] (maybe useless) && */line[i] != ' ' && line[i] != '-') // let's parse the first element of the string.
		i++;
	if (line[i + 1] == ' ') // if the next element is a space, then it's a room
		return (1);
	else if (line[i + 1] == '-') // if it's a hyphen, then it's a path, so ignore.
		return (2);
	return (0); // else it's an error.
}

int		room_counter(char **map)
{
	int i;
	int	room_nb;

	i = 0;
	room_nb = 0;
	while (map[i])
	{
		if (room_or_path(map[i]) == 1)
			room_nb++;
		i++;
	}
	return (room_nb);
}

void	room_parser(char *line, t_info *info, int j) // parses every classic room data.
{
	int		i;
	int		start;

	i = 0;
	room_init(&info->room_tab[j]);
	while (line[i] && line[i] != ' ') // let's grab the first element of the string (room name).
		i++;
	info->room_tab[j].id = j;
	info->room_tab[j].name = ft_strsub(line, 0, i);
	i++; // jumps over the ' '
	start = i;
	while (line[i] && line[i] != ' ') // let's grab the second element of the string (coord x).
		i++;
	info->room_tab[j].x = ft_atoi(ft_strsub(line, start, i));
	i++; // jumps over the ' '
	start = i;
	while (line[i] && line[i] != ' ') // let's grab the last element of the string (coord y).
		i++;
	info->room_tab[j].y = ft_atoi(ft_strsub(line, start, i));
}

void	room_add_start_end(char **map, t_info *info)
{
	if (!info->end_nb || !info->start_nb)
		parsing_error(map);
	room_parser(map[info->start_nb], info, 0);
	info->room_tab[0].type = 's';
	room_parser(map[info->end_nb], info, info->room_nb - 1);
	info->room_tab[info->room_nb - 1].type = 'e';
}

void	gates_manager(char **map, t_info *info, int ret, int i) // manages the gates' (start and end rooms) info.
{
	int		j;

	i += 1; // go to the next line to fetch either start or end data.
	j = 0;
	if ((ret == 2 && info->s_enc) || (ret == 3 && info->e_enc)) // if this is the second start or end, error.
		parsing_error(map);
	if ((info->s_enc = (ret == 2))) // if the command is "start", then the line contains the start room's map.
		info->start_nb = i; // marks the line of the start name and coordinates.
	else if ((info->e_enc = (ret == 3)))
		info->end_nb = i; // marks the line of the start name and coordinates.
}

int		hash_line_manager(char **map, int i) // does what is needed for lines starting with #.
{
	char	*command;

	if (!map[i][1]) // if the line was just one single '#', ignore.
		return (1);
	else if (map[i][1] != '#') // if the first line character is a # and not the next one, it's a comment, so move on.
		return (1);
	else if (map[i][1] == '#') // if there's another # after, then it might be a command.
	{
		if (map[i][2] == '#') // if the line start with "###", then it isn't well formatted, move on.
			return (1);
		else // else it might be a command : let's fetch it to see if it exists.
		{
			command = ft_strsub(map[i], 2, ft_strlen(map[i] - 2));
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

void	lem_in_parser(char **map, t_info *info) // parses the given map to get various info.
{
    int     i;
    int     j;
	int		ret;
	int		ant_nb;

    i = 1; // map[0] has already been treated above, now we can proceed to parse the rest.
	while (map[i])
    {
		if (map[i][0] == 'L') // lines can't start with L. If they do, output error.
			parsing_error(map);
		if (map[i][0] == '#') // if it starts with #, it might be a comment or a command:
		{
			ret = hash_line_manager(map, i); // this function will increment i to ignore the current line if necessary.
        	((ret == 2) || (ret == 3)) ? gates_manager(map, info, ret, i) : 0; // if ret is 2 or 3, it means start or end was encountered
			i += (ret == 1) ? 1 : 2; // if it's a comment, we just ignore this line, if it's a command we also ignore the next one.
		}
		else if ((map[i][0] >= 33 && map[i][0] <= 126)) // if it starts with a letter, number or special character, it might be a room or a path:
		{
			((room_or_path(map[i])) == 0) ? parsing_error(map) : 0;
			j = 1; // initialized at 1 to ignore the first slot of the array, dedicated to start room
			while ((room_or_path(map[i])) == 1) // while we go through the room lines, fill the struct array and increment i.
			{
				room_parser(map[i], info, j);
				i++;
				j++;
			}
		}
		i++;
    }
	room_add_start_end(map, info);
}
