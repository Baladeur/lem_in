/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:33:20 by myener            #+#    #+#             */
/*   Updated: 2019/12/04 16:05:05 by myener           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H
# define MAX_INT 2147483647
# define MIN_INT -2147483648
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct			s_info // useful information that may bee needed regularly.
{
	int		room_nb; 		// the number of rooms.
	int		ant_nb;			// the total number of ants.
	int		start_nb; 		// line number of start room coordinates, from input data array.
	int		end_nb; 		// line number of the end room.
	bool	s_enc;			// true if start is encountered, false if not.
	bool	e_enc;			// true if end is encountered, false if not.
}						t_info;

typedef struct			s_room  // for start room, end room, and classic in-between rooms.
{
		int				id;				// integer identifying the room.
        char            *name;          // name of the room.
		int				x;				// position of the room (easting).
		int				y;				// position of the room (northing).
        char            type;           // 's' if start room, 'e' if end room, 'c' if classic room.
        int             ant_nb_curr;    // nb of ants currently present. can only be <= 1 if type is 'c'.
                                        // when equal to base nb, current iteration is the first.
    	int				**matrix;
		struct s_room	*next;			// may be unnecessary.
		struct s_room	*prev;			// may be unnecessary.
}			        	t_room;

typedef struct			s_ant   // a means of registrating each ant, and their progress through the maze.
{
	int             id;         // registration number for each ant, going from 1 to the max number of ants.
	int		        position;      	// room id they are located in currently. can be equal to any *name in t_gate or t_room.
	struct s_ant	*next;
	struct s_ant	*prev;          // may be unnecessary.

}						t_ant;

typedef struct			s_path	// Register informations about a path
{
	int	*nodes;					// Tab of size room_nb. nodes[i] = 1 if the path goes through the room i, 0 otherwise.
	int	*edges;					// Order of the rooms (id) the path goes through, ex: 5, 2, 3, 0.
	int len;					// Length of the path aka number of rooms the path goes through
}						t_path;

typedef struct			s_paths	// A group of paths that are compatible with each other (chained list)
{
	int				*nodes;				// nodes[i] = 1 if one of the group's path goes through the room i, 0 otherwise.
	int				*count;				// Number of paths in the group.
	t_path			*path;				// Group's current path.
	struct s_paths	*next;				// Group's next path.
}						t_paths;

t_room			*room_malloc(t_room *node);
t_ant			*ant_malloc(t_ant *node);
char			**get_data(char **av, char **data);
t_ant     		*lem_in_parser(char **data, t_room *room_list, t_ant *ant_list);

int				**init_matrix(int count);
int				**destroy_matrix(int ***matrix);
void			print_matrix(int **matrix, int count);
int				**adj_matrix(char **data, t_room *farm, int count, int start);

t_room			*find_room(t_room *farm, char *name);

t_path			*new_path(int *edges, int count);
t_paths			*new_paths(t_path *path, int count);
t_paths			*add_path(t_paths *paths, t_path *path, int count);
t_path			*destroy_path(t_path **path);
t_paths			*destroy_paths(t_paths **paths);
void			print_path(t_path *path, int count);
void			print_paths(t_paths *paths, int count);

#endif
