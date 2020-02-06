/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:51:44 by myener            #+#    #+#             */
/*   Updated: 2018/11/27 16:11:53 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dst_ln;
	size_t	src_ln;

	src_ln = ft_strlen(src);
	dst_ln = ft_strnlen(dst, n);
	if (dst_ln == n)
		return (n + src_ln);
	if ((src_ln + dst_ln) < n)
		ft_memcpy((dst + dst_ln), src, (src_ln + 1));
	else
	{
		ft_memcpy((dst + dst_ln), src, ((n - dst_ln) - 1));
		dst[n - 1] = '\0';
	}
	return (dst_ln + src_ln);
}
