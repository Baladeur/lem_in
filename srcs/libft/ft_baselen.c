/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_baselen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:23:44 by myener            #+#    #+#             */
/*   Updated: 2019/03/13 17:26:47 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_baselen(long long int n, int len)
{
	int	e;

	e = 1;
	while ((n / len) > 0)
	{
		n /= len;
		e++;
	}
	return (e);
}
