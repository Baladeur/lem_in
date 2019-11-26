/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:24 by myener            #+#    #+#             */
/*   Updated: 2019/11/22 17:28:41 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char		**get_data(char **inst)
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
		(stock[i] == '\n' && stock[i + 1] == '\n') ? ps_output(1) : 0;
		i++;
	}
	inst = ft_strsplit(stock, '\n');
	inst = append_return(inst);
	ft_strdel(&stock);
	return (inst);
}
