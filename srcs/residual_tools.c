/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   residual_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:20:14 by tferrieu          #+#    #+#             */
/*   Updated: 2020/03/08 18:55:54 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lem_in.h"

t_residual	*residual_free(t_residual **residual, t_info *info, int b);

int			residual_update(t_residual *residual, t_path *path, t_info *info);

int			residual_init(t_residual *residual, t_tab **layout, t_info *info);

t_residual	*residual_create(t_tab **layout, t_tab *bfs, t_info *info);