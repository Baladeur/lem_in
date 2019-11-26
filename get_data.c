/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:24 by myener            #+#    #+#             */
/*   Updated: 2019/11/26 16:45:59 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
