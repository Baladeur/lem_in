/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:03:15 by myener            #+#    #+#             */
/*   Updated: 2019/08/12 16:18:14 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && (ft_isblank(s[i]) || s[i] == '\n'))
		i++;
	if (i == ft_strlen(s))
		return (ft_strnew(1));
	j = 0;
	len = ft_strlen(s);
	while (s[len - j - 1] == ' ' || s[len - j - 1] == '\t'
	|| s[len - j - 1] == '\n')
		j++;
	return (ft_strndup((s + i), (len - i - j)));
}
