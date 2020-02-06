/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 11:38:41 by myener            #+#    #+#             */
/*   Updated: 2018/11/27 16:12:49 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return (((char*)s) + ft_strlen((char*)s));
	while (s[i])
	{
		if (s[i] == c)
			return (((char*)s) + i);
		i++;
	}
	return (NULL);
}
