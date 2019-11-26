/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:52:20 by myener            #+#    #+#             */
/*   Updated: 2018/11/27 16:14:06 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char		*src2;
	unsigned char			*dst2;
	size_t					i;

	i = 0;
	src2 = (const unsigned char*)src;
	dst2 = (unsigned char*)dst;
	while (i < n)
	{
		dst2[i] = src2[i];
		if (src2[i] == ((unsigned char)c))
			return (dst2 + i + 1);
		i++;
	}
	return (0);
}
