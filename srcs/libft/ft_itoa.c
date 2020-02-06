/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:36:30 by myener            #+#    #+#             */
/*   Updated: 2019/03/13 17:25:14 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		i;
	int		neg;
	char	*str;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	neg = n < 0 ? 1 : 0;
	n = neg == 1 ? n * -1 : n;
	i = ft_intlen(n) + neg;
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
