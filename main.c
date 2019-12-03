/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:40:33 by myener            #+#    #+#             */
/*   Updated: 2019/12/03 18:20:44 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int     main(int argc, char **argv)
{
    t_room  *room_list;
    t_ant   *ant_list;
    char    **data;

    room_list = NULL;
    data = get_data(data);
    lem_in_parser(data, room_list, ant_list);
    return (0);
}