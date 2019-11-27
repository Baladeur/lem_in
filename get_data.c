/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:24 by myener            #+#    #+#             */
/*   Updated: 2019/11/27 19:23:48 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	gates_manager(char **data, t_room *rooms, int ret, int i) // manages the gates' (start and end rooms) info.
{
	int		j;
	t_info	*info;

	i += 1; // go to the next line to fetch either start or end data.
	j = 0;
	if (ret == 2) // if the command is "start", then the following line contains the start room's data.
	{
		while[i][j]
	}
	else if (ret == 3)
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

int     get_counts(char **data, t_room *rooms) // parses the given data to get various info.
{
    int     i;
    int     j;
	int		ret;
	int		ant_nb;
	t_info	info;

	if ((ant_nb = ft_atoi(data[0])) <= 0) // if the number of ants is equal to 0 or negative, we stop.
	{
		tab_free(data);
		ft_putendl("ERROR");
		return (0);
	}
	info.ant_nb = ant_nb;
    i = 1; // data[0] has already been treated above, now we can proceed to parse the rest.
    while (data[i])
    {
        j = 0;
		if (data[i][0] == '#')
			ret = hash_line_manager(data, i); // this function will increment i to ignore the current line if it is deemed necessary.
        ((ret == 2) || (ret == 3)) ? gates_manager(data, &info, ret, i) : 0; // if ret is 2 or 3, it means start or end was encountered
		i += (ret == 1) ? 1 : 0;
		while (data[i][j])
        {
            j++;
        }
        i++;
    }
    return (0);
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
