/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:38:41 by myener            #+#    #+#             */
/*   Updated: 2018/11/27 16:12:19 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		min;
	int		max;
	char	temp;

	min = 0;
	max = ft_strlen(str);
	max--;
	while (min < max)
	{
		temp = str[max];
		str[max] = str[min];
		str[min] = temp;
		min++;
		max--;
	}
	return (str);
}
