/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tferrieu <tferrieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:33:20 by myener            #+#    #+#             */
/*   Updated: 2020/06/02 19:56:54 by tferrieu         ###   ########.fr       */
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

typedef struct		s_ant
{
	int				id;
	int				i;
	int				pos;
	int				*path;
}					t_ant;

typedef struct		s_room
{
	int				id;
	int				x;
	int				y;
	char			*name;
	char			type;
}					t_room;

typedef struct		s_info
{
	int				room_nb;
	int				ant_nb;
	int				line_nb;
	t_ant			*ant;
	int				start_nb;
	int				end_nb;
	int				rooms_line;
	bool			s_enc;
	bool			e_enc;
	int				path_nb;
	int				**matrix;
	t_room			*room_tab;
}					t_info;

typedef struct		s_path
{
	int				*edges;
	int				len;
}					t_path;

typedef struct		s_queue
{
	struct s_queue	*next;
	int				id;
}					t_queue;

typedef struct		s_elist
{
	struct s_elist	*next;
	int				*edges;
}					t_elist;

int					string_free(char *str, int ret);
void				display_map(char **map);
int					is_room(char *line);
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
int					adj_matrix(char **data, t_info *info);

t_queue				*queue_new(int id);
int					queue_delone(t_queue **queue);
t_queue				*queue_add(t_queue **queue, int id);
int					queue_size(t_queue *queue);

int					path_exist(t_info *info);
t_path				*path_free(t_path **path, int b);
t_path				*path_init(int s, t_info *info);
int					path_add(t_path *path, int *edges, t_info *info, int b);
int					path_efficiency(t_path *path, int n);

t_elist				*elist_new(int *edges);
void				elist_delone(t_elist **list, int b);
t_elist				*elist_add(t_elist **list, int *edges);
int					elist_size(t_elist *list);

void				assign_path(t_path *path, t_info *info);

int					overlap_handler(t_elist *p, int **m, t_info *i, t_path **b);
int					suurballe(t_info *info, t_path **best);

#endif
