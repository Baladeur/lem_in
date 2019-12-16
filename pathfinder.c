/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:20:12 by myener            #+#    #+#             */
/*   Updated: 2019/12/16 22:21:30 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

lem_in_pathfinder(t_room *tab) // some pseudocode
{
	int		i;

	i = 0;
	path = CreatePath();
	path.enfiler(tab[i]); // ajouter la start room au début du bon chemin
	marquer(tab[i]); // marquer la start room comme visitée
	while ()// tant que l'id de la room rencontrée n'est pas égal à room_nb - 1 (aka l'end id)
	{
		tab[i] = path.defiler();
		afficher(tab[i]);
		pour tout voisin t de tab[i]
			si t non marqué
				path.enfiler(t);
				marquer(t);
		i++;
	}
}
