/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 17:38:41 by myener            #+#    #+#             */
/*   Updated: 2018/11/27 16:11:51 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen(s) - 1;
	if (!(*s))
		return (NULL);
	if (c == '\0')
		return (((char*)s) + ft_strlen((char*)s));
	while (i >= 0)
	{
		if (s[i] == c)
			return (((char*)s) + i);
		i--;
	}
	return (NULL);
}
