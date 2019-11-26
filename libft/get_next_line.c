/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 17:23:52 by myener            #+#    #+#             */
/*   Updated: 2019/11/20 18:20:01 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_n_strndup(char *str, char *dest, size_t n)
{
	size_t	i;

	if (!(dest = ft_strnew(n)))
		return (0);
	i = 0;
	while (i < n && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void			ft_spacesaver(char **stock, char **tmp, char **line, size_t i)
{
	*line = ft_n_strndup(*stock, *line, i);
	if (i < ft_strlen(*stock))
	{
		*tmp = *stock;
		*stock = ft_strdup(*stock + i + 1);
		free(*tmp);
	}
	else
		ft_strdel(stock);
}

int				get_next_line(const int fd, char **line)
{
	int				readsize;
	char			buffer[BUFF_SIZE + 1];
	static char		*stock = NULL;
	char			*tmp;

	if (fd < 0 || fd > MAX_FD || !line || !BUFF_SIZE || read(fd, stock, 0) < 0)
		return (-1);
	(!stock) ? stock = ft_strnew(0) : 0;
	while ((readsize = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[readsize] = '\0';
		if (!(stock = ft_free_join(stock, buffer)))
			return (-1);
		if (ft_strchr(stock, '\n'))
			break ;
	}
	if ((readsize < BUFF_SIZE) && (ft_strlen(stock) == 0))
	{
		free(stock);
		return (0);
	}
	ft_spacesaver(&stock, &tmp, line, ft_linelen(stock));
	return (1);
}
