/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:33:20 by myener            #+#    #+#             */
/*   Updated: 2020/03/12 17:06:36 by tferrieu         ###   ########.fr       */
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

typedef struct		s_ant		// every ant, its ID and the path it musts follow.
{
	int				id;				// ant's ID (starts from 1 to ant_nb).
	int				i;				// index for given path.
	int				pos;			// ant's current position.
	int				*path;			// ant's given path.
}					t_ant;

typedef struct		s_room		// for start room, end room, and classic in-between rooms.
{
	int				id;				// integer identifying the room.
	int				x;				// position of the room (easting).
	int				y;				// position of the room (northing).
	char			*name;			// name of the room.
	char			type;			// 's' if start room, 'e' if end room, 'c' if classic room.
	int				ant_nb_curr;	// nb of ants currently present. can only be <= 1 if type is 'c'.
									// when equal to base nb, current iteration is the first.
}					t_room;

typedef struct		s_info		// useful information that may bee needed regularly.
{
	int				room_nb;		// the number of rooms.
	int				ant_nb;			// the total number of ants.
	t_ant			*ant;			// a tab containing all the ants numbered (ant 1 is in pos 0, and so on) + their position (room id).
	int				start_nb;		// line number of start room coordinates, from input data array.
	int				end_nb;			// line number of the end room.
	int				edges_line;		// line number of the beginning of the edges list.
	int				rooms_line;		// line number of the beginning of the rooms list.
	bool			s_enc;			// true if start is encountered, false if not.
	bool			e_enc;			// true if end is encountered, false if not.
	int				path_nb;		// number of simultaneous paths found.
	int				**matrix;		// the adjacency matrix
	int				**dir_matrix;	// the directed adjacency matrix
	t_room			*room_tab;		// array of structures containing all rooms.
}					t_info;

typedef struct		s_path		// informations about a path.
{
	int				*edges;			// order of the rooms (id) the path goes through, ex: 5, 2, 3, 0.
	int 			len;			// length of the path aka number of rooms the path goes through.
}					t_path;

typedef struct		s_queue		// simple chained list to store room ids in a queue.
{
	struct s_queue	*next;			// next element in the queue.
	int				id;				// room id of the current element.
}					t_queue;

typedef struct		s_branch	// information stored for the pre_cleaner branching.
{
	t_queue			*queue;			// room queue for the BFS-inspired branching.
	int				**matrix;		// resulting directed branch matrix.
	int				*visited;		// the visited rooms, where visited[id] is the turn at which the room was visited, or -1.
	int				*weight;		// weight of each room, ex: weight[id] = 3 if 3 paths arrived at id at once during the branching.
	int				size;			// size of the ant farm aka the number of rooms.
}					t_branch;

typedef struct		s_elist		// simple chained list to store path edges.
{
	struct s_elist	*next;			// next element in the list.
	int				*edges;			// path node of the current element.
}					t_elist;

void				ant_free(t_info *info);
int					string_free(char *str, int ret);
void				display_map(char **map);
int					is_room(char *line);
void				lem_in_dispatcher(t_info *info, t_ant *ant);
void				lem_in_displayer(t_info *info, char **map);
int					lem_in_error_output(void);
int					lem_in_free(char **map, t_info *info, t_path **path, int b);
int					lem_in_parser(char **map, t_info *info);
void				room_free(t_info *info);
int					troubleshooter(t_info *info);

int					lem_init(t_info *info, char **map);
int					lem_in_atoi(char *str, int *ret);

int					**init_matrix(int count);
int					**matrix_free(int ***matrix, int count);
int					**dupe_matrix(int **matrix, int count);
int					adj_matrix(char **data, t_info *info);
void				sum_matrix(int **dest, int **src, int size);
void				print_matrix(int **matrix, int count);

t_queue				*queue_new(int id);
int					queue_delone(t_queue **queue);
t_queue				*queue_add(t_queue **queue, int id);
int					queue_get_at(t_queue *queue, int i);
int					queue_size(t_queue *queue);

t_branch			*init_branching(int size);
t_branch			*reset_branching(t_branch **branch, int i);
t_branch			*destroy_branching(t_branch **branch);
int					directed_matrix(t_info *info);
int					fill_gaps(t_info *info);

int					path_exist(t_info *info);
t_path				*path_free(t_path **path, int b);
t_path				*path_init(int s, t_info *info);
int					path_add(t_path *path, int *edges, t_info *info, int b);
int					path_remove(t_path *path, t_info *info);
int					path_efficiency(t_path *path, int n);

t_elist				*elist_new(int *edges);
void				elist_delone(t_elist **list, int b);
t_elist				*elist_add(t_elist **list, int *edges);
int					elist_size(t_elist *list);

t_path				*allpath(t_info *info, int *max);
int					pathfinder(t_info *info, t_path **best);

void				assign_path(t_path *path, t_info *info);

#endif
