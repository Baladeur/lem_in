/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 12:50:37 by myener            #+#    #+#             */
/*   Updated: 2018/11/29 12:48:23 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*new;
	t_list		*tmp;

	tmp = f(lst);
	new = tmp;
	if (lst)
	{
		while (lst->next && (tmp->next = f(lst)))
		{
			lst = lst->next;
			if (!(tmp->next = f(lst)))
			{
				free(tmp->next);
				return (NULL);
			}
			tmp = tmp->next;
		}
	}
	return (new);
}
