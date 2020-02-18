/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:24 by myener            #+#    #+#             */
/*   Updated: 2020/02/18 19:09:49 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static void		room_parser(char *line, t_info *info, int j) // parses every classic room data.
{
	int		i;
	int		start;

	i = 0;
	room_init(&info->room_tab[j]);
	while (line[i] && line[i] != ' ') // let's grab the first element of the string (room name).
		i++;
	info->room_tab[j].id = j;
	info->room_tab[j].name = ft_strsub(line, 0, i);
	// printf("name = %s\n\n", info->room_tab[j].name);
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

static void		room_add_start_end(char **map, t_info *info)
{
	if (!info->end_nb || !info->start_nb)
		parsing_error(map);
	room_parser(map[info->start_nb], info, 0);
	info->room_tab[0].type = 's';
	room_parser(map[info->end_nb], info, info->room_nb - 1);
	info->room_tab[info->room_nb - 1].type = 'e';
}

static void		gates_manager(char **map, t_info *info, int ret, int i) // manages the gates' (start and end rooms) info.
{
	int		j;

	i += 1; // go to the next line to fetch either start or end data.
	j = 0;
	if ((ret == 2 && info->s_enc) || (ret == 3 && info->e_enc)) // if this is the second start or end, error.
		parsing_error(map);
	if ((info->s_enc = (ret == 2))) // if the command is "start", then the line contains the start room's map.
		info->start_nb = i; // marks the line number of the start coordinates.
	else if ((info->e_enc = (ret == 3)))
		info->end_nb = i; // marks the line number of the end coordinates.
}

static int		hash_line_manager(char **map, int i) // does what is needed for lines starting with #.
{
	char	*command;

	command = NULL;
	if (!map[i][1] || map[i][1] != '#') // if the line was just one single '#' or starts with just one, it's a comment, ignore.
		return (1);
	else if (map[i][1] == '#') // if there's another # after, then it might be a command.
	{
		if (map[i][2] == '#') // if the line start with "###", then it isn't well formatted, move on.
			return (1);
		else // else it might be a command : let's fetch it to see if it exists.
		{
			command = ft_strsub(map[i], 2, ft_strlen(map[i]));
			if (!(ft_strcmp(command, "start\n")))
				return (2);
			else if (!(ft_strcmp(command, "end\n")))
				return (3);
			else // else the command doesn't exist, so move on.
				return (1);
		}
	}
	return (0);
}

void			lem_in_parser(char **map, t_info *info) // parses the given map to get various info.
{
    int     i;
    int     j;
	int		ret;

    i = 1; // map[0] has already been treated, now we can proceed to parse the rest.
	j = 0;
	while (map[i])
    {
		// printf("map[i] = %s\n", map[i]);
		if (map[i][0] == 'L') // lines can't start with L. If they do, output error.
			parsing_error(map);
		if (map[i][0] == '#') // if it starts with #, it might be a comment or a command:
		{
			ret = hash_line_manager(map, i); // this function will increment i to ignore the current line if necessary.
			((ret == 2) || (ret == 3)) ? gates_manager(map, info, ret, i) : 0; // if ret is 2 or 3, it means start or end was encountered
			i += (ret == 1) ? 0 : 1; // if it's a comment, we just ignore this line, if it's a command we also ignore the next one.
		}
		else if ((map[i][0] >= 33 && map[i][0] <= 126)) // if it starts with a letter, number or special character, it might be a room or a path:
		{
			// ((is_room(map[i])) == 0) ? parsing_error(map) : 0;
			j = (j == 0) ? 1 : j; // initialized at 1 to ignore the first slot of the struct array, dedicated to start room
			if (is_room(map[i])) // while we go through the room lines, fill the struct array and increment i.
			{
				room_parser(map[i], info, j);
				j++;
			}
			if ((i - 1) > 1 && is_room(map[i - 1]) && !is_room(map[i])) // if the precedent line is a room and the current one isn't, then it's the first line of paths. save it.
				info->edges_line = i;
		}
		i++;
    }
	room_add_start_end(map, info); // add the start and end room at beginning end of the array.
}
