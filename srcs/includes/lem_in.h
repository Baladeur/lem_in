/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myener <myener@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:33:20 by myener            #+#    #+#             */
/*   Updated: 2020/02/06 10:19:55 by myener           ###   ########.fr       */
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
# include "../libft/libft.h"

typedef struct 			s_ant		// every ant, its ID and the path it musts follow.
{
	int				id;				// ant's id.
	int				pos;			// ant's current position.
	int				*path;			// ant's given path.
}						t_ant;

typedef struct			s_room		// for start room, end room, and classic in-between rooms.
{
	int				id;				// integer identifying the room.
	int				x;				// position of the room (easting).
	int				y;				// position of the room (northing).
    char            *name;          // name of the room.
    char            type;           // 's' if start room, 'e' if end room, 'c' if classic room.
    int             ant_nb_curr;    // nb of ants currently present. can only be <= 1 if type is 'c'.
                                    // when equal to base nb, current iteration is the first.
}			        	t_room;

typedef struct			s_info		// useful information that may bee needed regularly.
{
	int				room_nb; 		// the number of rooms.
	int				ant_nb;			// the total number of ants.
	t_ant			*ant;			// a tab containing all the ants numbered (ant 1 is in pos 0, and so on) + their position (room id).
	int				start_nb; 		// line number of start room coordinates, from input data array.
	int				end_nb; 		// line number of the end room.
	bool			s_enc;			// true if start is encountered, false if not.
	bool			e_enc;			// true if end is encountered, false if not.
    int				path_nb;		// number of simultaneous paths found.
	int				**matrix;		// the adjacency matrix
	t_room			*room_tab;		// array of structures containing all rooms.
}						t_info;

typedef struct			s_path		// informations about a path.
{
	int				*nodes;			// tab of size room_nb. nodes[i] = 1 if the path goes through the room i, 0 otherwise.
	int				*edges;			// order of the rooms (id) the path goes through, ex: 5, 2, 3, 0.
	int 			len;			// length of the path aka number of rooms the path goes through.
}						t_path;

typedef struct			s_queue		// simple chained list to store room ids in a queue.
{
	struct s_queue	*next;			// next element in the queue.
	int				id;				// room id of the current element.
}						t_queue;

typedef struct			s_branch	// information stored for the pre_cleaner branching.
{
	t_queue	*queue;					// room queue for the BFS-inspired branching.
	int		**matrix;				// resulting directed branch matrix.
	int		*visited;				// the visited rooms, where visited[id] is the turn at which the room was visited, or -1.
	int		*weight;				// weight of each room, ex: weight[id] = 3 if 3 paths arrived at id at once during the branching.
	int		size;					// size of the ant farm aka the number of rooms.
}						t_branch;


void		ant_init(t_info *info);
int			error_output(void);
void		free_struct_array(t_info *info);
char		**get_map(char **av, char **data);
char		*get_room_name(t_info *info, int room_id);
void		info_init(t_info *info);
int			is_room(char *line);
void		lem_in_dispatcher(t_info *info, t_path *path_tab);
void		lem_in_displayer(t_info *info, t_path *path_tab, char **map);
void     	lem_in_parser(char **map, t_info *info);
int			parsing_error(char **map);
void		room_init(t_room *room);
int			troubleshooter(t_info *info);

int			**init_matrix(int count);
int			**destroy_matrix(int ***matrix);
int			**dupe_matrix(int **matrix, int count);
int			**adj_matrix(char **data, t_room *farm, t_info *info, int start);
void		sum_matrix(int **dest, int **src, int size);
void		print_matrix(int **matrix, int count);

int			find_room(t_room *farm, char *name, t_info *info);

t_queue		*queue_new(int id);
void		queue_delone(t_queue **queue);
t_queue		*queue_add(t_queue **queue, int id);
int			queue_get_at(t_queue *queue, int i);
int			queue_size(t_queue *queue);

t_branch	*init_branching(int size);
t_branch	*reset_branching(t_branch **branch, int i);
t_branch	*destroy_branching(t_branch **branch);
int			**pre_cleaner(int **matrix, t_info *info);

#endif
