#include "includes/lem_in.h"

typedef struct	s_queue_c
{
	struct	s_queue_c	*next;
	int					cost;
	int					pos;
}				t_queue_c;

typedef struct	s_pathtab
{
	struct s_pathtab	*next;
	t_path				*tab;
}				t_pathtab;

typedef struct	s_tab
{
	int p;
	int d;
}				t_tab;


/*
** Deletes the first element of the given queue.
*/

int				queue_c_delone(t_queue_c **queue)
{
	t_queue_c	**tmp;

	tmp = NULL;
	if (queue && *queue && ((tmp = (*queue)->next) || 1))
		free(*queue);
	*queue = tmp;
	return (0);
}

/*
** Adds an element to the queue so that it remains sorted ascendingly.
** Returns 0 if malloc fails, 1 otherwise.
*/

int				queue_c_add(t_queue_c **queue, int pos, int cost)
{
}

/*
** Deletes the first element of a pathtab list.
*/

int				pathtab_delone(t_pathtab **pathtab)
{
}

/*
** Adds a path to a pathtab.
*/

int				pathtab_add(t_pathtab **pathtab, t_path *path)
{
}

/*
** Stores the distance to each vertex from the starting room, given a graph.
*/

int				bfs_dist(int **matrix, t_info *info, t_tab *tab)
{
}

/*
** Returns a list of edges corresponding to every path with the minimal cost.
*/

t_elist			*allminpath(int **matrix, int min_cost, t_info *info)
{
}

/*
** Returns a list of combination of every path with the minimal cost.
*/

t_pathtab		*allminpathtabs(t_elist *allpath, t_info *info)
{
}

int				backtrack(t_info *info)
{
	// IF CURRENT PATHTAB > STORED PATHTAB
		// REPLACE PATHTAB
	// DFS ALL SHORTEST PATH
	// CREATE RESIDUAL GRAPH
	// FOR EACH SHORTEST PATH COMBINATION
		// UPDATE RESIDUAL GRAPH
		// BT WITH CURRENT SHORTEST PATH COMBINATION
		// RESTORE RESIDUAL GRAPH
}

t_path			*pathfinding(t_info *info)
{
}