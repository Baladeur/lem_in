/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathtab_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:36:05 by tferrieu          #+#    #+#             */
/*   Updated: 2020/02/03 18:36:05 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path  *pathtab_destroy(t_path **pathtab, int count)
{
    int i;

    if (!pathtab || *pathtab)
        return (NULL);
    i = -1;
    while (++i < count && pathtab[0][i].len > 0)
    {
        if (pathtab[0][i].nodes)
            free(pathtab[0][i].nodes);
        if (pathtab[0][i].edges)
            free(pathtab[0][i].edges);
    }
    free(pathtab[0]);
    pathtab[0] = NULL;
    return (NULL);
}

t_path  *pathtab_init(int count)
{
    t_path  *pathtab;

    if (!(pathtab = (t_path *)malloc(sizeof(t_path) * (count + 1))))
        return (NULL);
}



int     *pathtab_capacity(t_path *pathtab, int count, t_info *info)
{
    int i;
    int total;
    int longest;
}