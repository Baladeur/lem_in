/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:15:33 by myener            #+#    #+#             */
/*   Updated: 2019/03/13 17:25:20 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long int n, const char *base)
{
	int		i;
	int		bl;
	int		neg;
	char	*str;

	bl = ft_strlen(base);
	neg = n < 0 ? 1 : 0;
	n = neg == 1 ? n * -1 : n;
	i = ft_baselen(n, bl) + neg;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (1)
	{
		str[--i] = ((n % bl) + 48);
		n /= bl;
		if (n == 0)
			break ;
	}
	if (neg == 1)
		str[0] = '-';
	return (str);
}
