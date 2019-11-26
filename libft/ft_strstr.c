/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 16:41:44 by myener            #+#    #+#             */
/*   Updated: 2018/11/23 16:58:30 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *find)
{
	int	i;
	int	j;

	if (!*find)
		return ((char *)str);
	i = 0;
	while (str[i])
	{
		j = 1;
		if (str[i] == find[0])
		{
			while (find[j] != '\0' && str[i + j] == find[j])
				j++;
			if (find[j] == '\0')
				return ((char *)str + i);
		}
		i++;
	}
	return (0);
}
