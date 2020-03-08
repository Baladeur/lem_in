/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:19:39 by tferrieu          #+#    #+#             */
/*   Updated: 2020/03/08 18:56:55 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

static int	bfs_dist(t_tab **layout, t_suurballe *suurballe, t_tab *bfs);

static int	pathfinding_bt_exit();

int			pathfinding_bt(t_tab **layout, t_suurballe *suurballe);

t_path		*suurballe_pathfinding(t_info *info);