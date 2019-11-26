/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:11:23 by myener            #+#    #+#             */
/*   Updated: 2019/10/16 19:13:42 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_numword(char const *s, char c)
{
	size_t	numword;
	size_t	i;

	i = 0;
	numword = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] != '\0' && s[i] == c)
				i++;
		}
		if (s[i] != '\0' && s[i] != c)
		{
			numword++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (numword);
}

static size_t	ft_lenw(char const *s, size_t index, char c)
{
	size_t	len;

	len = 0;
	while (s[index] != '\0' && s[index] != c)
	{
		len++;
		index++;
	}
	return (len);
}

static char		**ft_filltab(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			k = 0;
			if (!(tab[j] = malloc(sizeof(char) * (ft_lenw(s, i, c) + 1))))
				return (0);
			while (s[i] != '\0' && s[i] != c)
				tab[j][k++] = s[i++];
			tab[j++][k] = '\0';
		}
	}
	tab[j] = 0;
	return (tab);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;

	if (s)
	{
		if (!(tab = (char **)malloc(sizeof(char*) * (ft_numword(s, c) + 1))))
			return (0);
		tab = ft_filltab(tab, s, c);
		return (tab);
	}
	return (NULL);
}
