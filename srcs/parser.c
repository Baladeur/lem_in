/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:24 by myener            #+#    #+#             */
/*   Updated: 2020/03/12 18:24:13 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	room_parser(char *line, t_info *info, int j)
{
	int		i;
	int		end;
	char	*tmp;

	i = ft_strlen(line) - 2;
	end = i;
	tmp = NULL;
	while (i > 0 && line[i] != ' ' && line[i] != '-')
		i--;
	if (!i || line[++i - 2] == '-' || !(tmp = ft_strsub(line, i, end - i + 1)))
		return (0);
	if ((i -= 2) && !lem_in_atoi(tmp, &(info->room_tab[j].y)))
		return (string_free(tmp, 0));
	free(tmp);
	end = i;
	while (i > 0 && line[i] != ' ' && line[i] != '-')
		i--;
	if (!i || line[++i - 2] == '-' || !(tmp = ft_strsub(line, i, end - i + 1)))
		return (0);
	if ((i--) >= 0 && !lem_in_atoi(tmp, &(info->room_tab[j].x)))
		return (string_free(tmp, 0));
	free(tmp);
	info->room_tab[j].id = j;
	info->room_tab[j].name = ft_strsub(line, 0, i);
	return (1);
}

static int	end_parser(char **map, t_info *info)
{
	if (!info->end_nb || !info->start_nb)
		return (0);
	if (!(room_parser(map[info->start_nb], info, 0)))
		return (0);
	info->room_tab[0].type = 's';
	if (!(room_parser(map[info->end_nb], info, info->room_nb - 1)))
		return (0);
	info->room_tab[info->room_nb - 1].type = 'e';
	return (1);
}

static int	gates_manager(t_info *info, int ret, int i, char **map)
{
	int		j;

	if (!map[i + 1] || !(is_room(map[i + 1]) > 0))
		return (0);
	i += 1;
	j = 0;
	if ((ret == 2 && info->s_enc) || (ret == 3 && info->e_enc))
		return (0);
	else if (ret == 2 && (info->s_enc = 1))
		info->start_nb = i;
	else if (ret == 3 && (info->e_enc = 1))
		info->end_nb = i;
	return (1);
}

static int	hash_line_manager(char **map, int i)
{
	char	*command;

	command = NULL;
	if (!map[i][1] || map[i][1] != '#')
		return (1);
	else
	{
		command = ft_strsub(map[i], 2, ft_strlen(map[i]));
		if (!(ft_strcmp(command, "start\n")))
			return (string_free(command, 2));
		else if (!(ft_strcmp(command, "end\n")))
			return (string_free(command, 3));
		else
			return (string_free(command, 1));
	}
}

int			lem_in_parser(char **map, t_info *info)
{
	int		i;
	int		j;
	int		ret;

	i = info->rooms_line;
	j = 0;
	while (map[++i])
	{
		if (map[i][0] == 'L')
			break ;
		if (map[i][0] == '#')
		{
			if ((ret = hash_line_manager(map, i)) > 1)
				if (!gates_manager(info, ret, i, map)
					&& (info->edges_line = i) >= 0)
					break ;
			i += (ret == 1) ? 0 : 1;
		}
		else if (map[i][0] >= 33 && map[i][0] <= 126)
			if (is_room(map[i]) == 1 && ++j)
				if (j >= info->room_nb - 1 || !room_parser(map[i], info, j))
					return (j >= info->room_nb - 1 ? end_parser(map, info) : 0);
	}
	return (end_parser(map, info));
}
