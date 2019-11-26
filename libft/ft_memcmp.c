/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:46:09 by myener            #+#    #+#             */
/*   Updated: 2018/11/27 16:14:02 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_cast;
	unsigned char	*s2_cast;

	s1_cast = (unsigned char*)s1;
	s2_cast = (unsigned char*)s2;
	while (n-- > 0)
	{
		if (*s1_cast != *s2_cast)
			return ((int)(*s1_cast - *s2_cast));
		s1_cast++;
		s2_cast++;
	}
	return (0);
}
