/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:24 by myener            #+#    #+#             */
/*   Updated: 2020/03/09 14:11:37 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	room_parser(char *line, t_info *info, int j)
{
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	tmp = NULL;
	room_init(&info->room_tab[j]);
	while (line[i] && line[i] != ' ')
		i++;
	info->room_tab[j].id = j;
	info->room_tab[j].name = ft_strsub(line, 0, i);
	i++;
	start = i;
	while (line[i] && line[i] != ' ')
		i++;
	tmp = ft_strsub(line, start, i);
	info->room_tab[j].x = ft_atoi(tmp);
	tmp ? free(tmp) : 0;
	start = i++;
	while (line[i] && line[i] != ' ')
		i++;
	tmp = ft_strsub(line, start, i);
	info->room_tab[j].y = ft_atoi(tmp);
	tmp ? free(tmp) : 0;
	return (1);
}

static int	room_add_start_end(char **map, t_info *info)
{
	if (!info->end_nb || !info->start_nb)
		return (0);
	room_parser(map[info->start_nb], info, 0);
	info->room_tab[0].type = 's';
	room_parser(map[info->end_nb], info, info->room_nb - 1);
	info->room_tab[info->room_nb - 1].type = 'e';
	return (1);
}

static int	gates_manager(t_info *info, int ret, int i)
{
	int		j;

	i += 1;
	j = 0;
	if ((ret == 2 && info->s_enc) || (ret == 3 && info->e_enc))
		return (0);
	if ((info->s_enc = (ret == 2)))
		info->start_nb = i;
	else if ((info->e_enc = (ret == 3)))
		info->end_nb = i;
	return (1);
}

static int	hash_line_manager(char **map, int i)
{
	char	*command;

	command = NULL;
	if (!map[i][1] || map[i][1] != '#')
		return (1);
	else if (map[i][1] == '#')
	{
		if (map[i][2] == '#')
			return (1);
		else
		{
			command = ft_strsub(map[i], 2, ft_strlen(map[i]));
			if (!(ft_strcmp(command, "start\n")))
				return (command_free(command, 2));
			else if (!(ft_strcmp(command, "end\n")))
				return (command_free(command, 3));
			else
				return (command_free(command, 1));
		}
	}
	return (0);
}

int			lem_in_parser(char **map, t_info *info)
{
	int		i;
	int		j;
	int		ret;

	i = 0;
	j = 0;
	while (map[++i])
	{
		if (map[i][0] == 'L')
			return (0);
		if (map[i][0] == '#')
		{
			if ((ret = hash_line_manager(map, i)) == 0)
				return (0);
			if ((ret == 2) || (ret == 3))
				if (!gates_manager(info, ret, i))
					return (0);
			i += (ret == 1) ? 0 : 1;
		}
		else if ((map[i][0] >= 33 && map[i][0] <= 126))
		{
			// ((is_room(map[i])) == 0) ? lem_in_map_free_error(map) : 0;
			j = (j == 0) ? 1 : j;
			j += is_room(map[i]) ? room_parser(map[i], info, j) : 0;
			if ((i - 1) > 1 && is_room(map[i - 1]) && !is_room(map[i]))
				info->edges_line = i;
		}
	}
	return (room_add_start_end(map, info) ? 1 : 0);
}
