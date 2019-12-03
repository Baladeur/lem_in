/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:24 by myener            #+#    #+#             */
/*   Updated: 2019/12/03 18:31:52 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		parsing_error(char **data)
{
	tab_free(data);
	ft_putendl("ERROR");
	return (0);
}

t_ant	*ant_parser(t_ant *ant_list, int ant_nb)
{
	int		i;
	t_ant	*tmp;
	t_ant	*head;

	ant_list = ant_malloc(ant_list); // malloc first node.
	tmp = ant_list;
	head = ant_list;
	ant_list->ant_id = 1; // give id to first node.
	i = 2;
	while (i <= ant_nb)
	{
		ant_list->next = ant_malloc(ant_list->next);
		ant_list = ant_list->next;
		ant_list->prev = tmp;
		tmp = ant_list;
		ant_list->ant_id = i;
		i++;
	}
	ant_list->next = NULL;
	return (head);
}

void	room_add_start_end(char **data, t_room *head, t_info *info)
{
	t_room	*tmp;
	t_room	*curr;

	curr = head; // first let's malloc a new head node and initialize the start room.
	tmp = curr;
	curr->prev = room_malloc(curr);
	curr = curr->prev;
	curr->next = tmp;
	room_parser_stocker(data[info->start_nb], curr);
	curr->id = 0;
	curr->type = 's';
	head = curr;
	while (curr && curr->next) // now let's malloc and initialize the last (end) room.
		curr = curr->next;
	tmp = curr;
	curr->next = room_malloc(curr->next);
	curr = curr->next;
	curr->prev = tmp;
	curr->next = NULL;
	room_parser_stocker(data[info->end_nb], curr);
	curr->type = 'e';
}

void	room_parser_stocker(char *line, t_room *room_list) // stocks individual room nodes with data.
{
	int		i;
	int		start;

	i = 0;
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

t_room	*room_parser(char *line, t_room *head) // parses every classic room data.
{
	t_room	*tmp;
	t_room	*room_list;

	room_list = head; // first we keep track of the head, as we will need to return it.
	if (!room_list) // if this is the first node, initialize accordingly.
	{
		room_list = room_malloc(room_list); // malloc and initializes the new node.
		room_list->prev = NULL; // initializes the first node's prev, aka NULL.
		room_list->next = NULL;// initializes the first node's next, aka NULL.
	}
	else if (room_list && room_list->name) // else if there's already at least one node, fill the next one.
	{
		while (room_list && room_list->name && room_list->next) // goes to the last element of the list.
			room_list = room_list->next;
		tmp = room_list; // stocks the last known node, which will be NULL if no node is already present.
		room_list->next = room_malloc(room_list->next); // malloc and initializes the new node.
		room_list = room_list->next; // goes to the new node;
		room_list->prev = tmp; // initializes the new last node's prev, aka the old last node.
		room_list->next = NULL;// initializes the new last node's next, aka NULL.
	}
	room_parser_stocker(line, room_list);
	return (head);
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

void     lem_in_parser(char **data, t_room *room_list, t_ant *ant_list) // parses the given data to get various info.
{
    int     i;
	int		ret;
	int		ant_nb;
	t_info	info;

	if ((ant_nb = ft_atoi(data[0])) <= 0) // if the number of ants is equal to 0 or negative, we stop.
		parsing_error(data);
	info.ant_nb = ant_nb;
	ant_list = ant_parser(ant_list, ant_nb);
    i = 1; // data[0] has already been treated above, now we can proceed to parse the rest.
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
			(ret = (room_or_path(data[i])) == 0) ? parsing_error(data) : 0;
			room_list = (ret == 1) ? room_parser(data[i], room_list) : room_list;
		}
		i++;
    }
	room_add_start_end(data, room_list, &info);
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
