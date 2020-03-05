#include "includes/lem_in.h"

typedef struct	s_queue_c
{
	struct	s_queue_c	*next;
	int					cost;
	int					pos;
}				t_queue_c;

typedef struct	s_pathlist
{
	struct s_pathlist	*next;
	t_path				*tab;
}				t_pathlist;

typedef struct	s_tab
{
	int p;
	int c;
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
	t_queue_c	*new;
	t_queue_c	*curr;

	if (!(new = (t_queue_c *)malloc(sizeof(t_queue_c))))
		return (0);
	new->pos = pos;
	new->cost = cost;
	if ((!queue ||!*queue) && (*queue = new))
		return (1);
	if (curr->cost > cost && (new->next = *queue)
		&& (*queue = new))
		return (1);
	curr = *queue;
	while (curr->next && curr->next->cost < cost)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
	return (1);
}

/*
** Returns the current size of the queue.
*/

int		queue_c_size(t_queue_c *queue)
{
	t_queue_c	*current;
	int			n;

	n = 0;
	current = queue;
	while (current)
	{
		n++;
		current = current->next;
	}
	return (n);
}

/*
** Deletes the first element of a pathlist list.
*/

int				pathlist_delone(t_pathlist **pathlist, int b)
{
	t_pathlist	*tmp;

	if (!pathlist || !*pathlist)
		return (0);
	tmp = (*pathlist)->next;
	if (b)
		path_free(&((*pathlist)->tab), 1);
	free(*pathlist);
	*pathlist = tmp;
	return (0);
}

/*
** Adds a path to a pathlist.
*/

int				pathlist_add(t_pathlist **pathlist, t_path *path)
{
	t_pathlist	*new;
	t_pathlist	*curr;

	if (!(new = (t_pathlist *)malloc(sizeof(t_pathlist))))
		return (0);
	new->next = NULL;
	new->tab = path;
	if ((!pathlist ||!*pathlist) && (*pathlist = new))
		return (1);
	curr = *pathlist;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	return (1);
}

/*
** Stores the distance to each vertex from the starting room, given a graph.
*/

int				bfs_dist(int ***matrix, t_info *info, t_tab *tab)
{
	t_queue_c	*queue;
	int			i;

	queue = NULL;
	if (!(queue_c_add(&queue, 0, 0)))
		return (0);
	while (queue)
	{
		i = -1;
		while (++i < info->room_nb - 1)
			if (matrix[0][queue->pos][i] && tab[i].c < 0)
			{
				tab[i].c = queue->cost + matrix[1][queue->pos][i];
				tab[i].p = queue->pos;
				if (!(queue_c_add(&queue, i, tab[i].c)))
				{
					while (queue)
						queue_c_delone(&queue);
					return (0);
				}
			}
		queue_c_delone(&queue);
	}
	return (1);
}

/*
** Returns a list of edges corresponding to every path with the minimal cost.
*/

static int	add_to_list(t_queue_c *parent, int pos, t_elist **list, int size)
{
	t_queue_c	*current;
	int			*edges;
	int			len;

	edges = NULL;
	len = queue_c_size(parent);
	if (!(edges = (int *)malloc(sizeof(int) * (len + 2))))
		return (0);
	current = parent;
	edges[len + 1] = size - 1;
	edges[len] = pos;
	while (--len > 0)
	{
		edges[len] = current->pos;
		current = current->next;
	}
	edges[len] = 0;
	if (!elist_add(list, edges))
	{
		free(edges);
		return (0);
	}
	return (1);
}

/*
** Backtracking used to find all edges with the minimal cost from start to end.
*/

static int	allminpath_bt(t_queue_c *parent, int ***matrix, int pos, t_elist *list)
{
	t_queue_c	*current;
	int			i;
	int			b;

	if ((i = -1) && matrix[0][pos][matrix[0][0][0] - 1])
		return (add_to_list(pos, parent, list, matrix[0][0][0]));
	b = 0;
	while (++i < matrix[0][0][0])
		if (matrix[0][pos][i] > 0 && pos != i && (b = 1))
			break ;
	if ((i = -1) && !b || parent->cost + matrix[1][parent->pos][pos] > matrix[1][0][0])
		return (1);
	if (!(current = queue_c_add(&current, 0, parent->cost + matrix[1][parent->pos][pos])))
		return (0);
	current->next = parent;
	while (++i < matrix[0][0][0])
		if (matrix[0][pos][i] > 0 && pos != i && (!parent || parent->pos != i))
			if (!(allminpath_bt(current, matrix, i, list)))
				return (queue_c_delone(&current));
	queue_c_delone(&current);
	return (1);
}

/*
** Returns a list of all edges with the minimal cost from start to end.
*/

t_elist			*allminpath(int ***matrix, int min_cost, t_info *info)
{
	t_elist	*list;

	list = NULL;
	matrix[0][0][0] = info->room_nb;
	matrix[1][0][0] = min_cost;
	if (!(allminpath_bt(NULL, matrix, 0, &list)))
	{
		while (list)
			elist_delone(&list, 1);
		return (NULL);
	}
	matrix[0][0][0] = 0;
	matrix[1][0][0] = 0;
	return (list);
}

/*
** Duplicates src path values into dest path values.
*/

static void	path_clone(t_path *src, t_path *dest, t_info *info)
{
	int i;
	int j;

	i = -1;
	while (src[++i].len >= 0 && (dest[i].len = src[i].len) >= 0)
		dest[i].edges = src[i].edges;
	j = -1;
	while (++j < info->room_nb - 1)
		dest[i].edges[j] = src[i].edges[j];
}

/*
** Compare src with dest. Returns 1 if src is better, 0 otherwise.
*/

static int	is_better(t_path *src, t_path *dst, int ant_nb)
{
	int i;
	int l1;
	int l2;

	if (path_efficiency(src, ant_nb) > path_efficiency(dst, ant_nb))
		return (0);
	if (path_efficiency(src, ant_nb) < path_efficiency(dst, ant_nb))
		return (1);
	l1 = 0;
	l2 = 0;
	i = -1;
	while (src[++i].len > 0)
		l1 += src[i].len;
	i = -1;
	while (dst[++i].len > 0)
		l2 += dst[i].len;
	return (l1 < l2);
}

int				***suurmatrix_free(int ****matrix, int size)
{
	if (!matrix || !(*matrix))
		return (NULL);
	if ((*matrix)[0])
		matrix_free(&((*matrix[0])), size);
	if ((*matrix)[1])
		matrix_free(&((*matrix[1])), size);
	free(*matrix);
	*matrix = NULL;
	return (NULL);
}

int				***init_suurmatrix(int size)
{
	int	***matrix;

	if (!(matrix = (int ***)malloc(sizeof(int **) * 2)))
		return (NULL);
	matrix[0] = NULL;
	matrix[1] = NULL;
	if (!(matrix[0] = init_matrix(size))
		|| !(matrix[0] = init_matrix(size)))
		return (suurmatrix_free(&matrix, size));
	return (matrix);
}

int				pathfinding_bt_exit(t_tab **tab, int ****new, t_info *info)
{
	if (tab && *tab)
		free(*tab);
	if (new && *new)
		suurmatrix_free(new, info->room_nb);
	return (0);
}

int				pathfinding_bt(t_path *best, t_path *curr, int ***matrix, t_info *info)
{
	t_elist		*allpath;
	t_tab		*tab;
	int			***new;
	int			i;

	allpath = NULL;
	new = NULL;
	tab = NULL;
	if (curr[0].len && (!best[0].len || is_better(curr, best, info->ant_nb)))
		path_clone(best, curr, info);
	if (!(tab = (t_tab *)malloc(sizeof(t_tab) * info->room_nb)))
		return (0);
	i = -1;
	while (++i < info->room_nb - 1 && (tab[i].p = -1))
		tab[i].c = -1;
	if (!(bfs_dist(matrix, info, tab)))
		return (pathfinding_bt_exit(&tab, &new, info));
	if (tab[i].p < 0)
	{
		free(tab);
		return (1);
	}
	if (!(allpath = allminpath(new, tab[i].c, info))
		|| !(new = init_suurmatrix(info->room_nb)))
		return (pathfinding_bt_exit(&tab, &new, info));
	// CREATE RESIDUAL GRAPH
	// CREATE SHORTEST PATH COMBINATION LIST
	// FOR EACH SHORTEST PATH COMBINATION
		// UPDATE RESIDUAL GRAPH
		// BT WITH CURRENT SHORTEST PATH COMBINATION
		// RESTORE RESIDUAL GRAPH
}

t_path			*pathfinding(t_info *info)
{
}