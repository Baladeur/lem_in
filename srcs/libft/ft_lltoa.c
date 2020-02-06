/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 12:27:49 by myener            #+#    #+#             */
/*   Updated: 2019/04/25 17:05:21 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lltoa(long long int n)
{
	int		i;
	int		neg;
	char	*str;

	if (n == 0)
		return (ft_strdup("0"));
	neg = n < 0 ? 1 : 0;
	n = neg == 1 ? n * -1 : n;
	i = ft_intlen(n) - 1 + neg + 1;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (n > 0)
	{
		str[--i] = ((n % 10) + 48);
		n /= 10;
	}
	if (neg == 1)
		str[0] = '-';
	return (str);
}
