#include "grim_fetcher.h"

static t_list	*init_astar(t_map *map, t_cell *start, t_cell *end);
static float	heuristic(t_cell *a, t_cell *b);
static void		neighbors(t_man *man, t_astar *a, t_list **list, t_cell *curr);
static int		cmp_global_goal(void *a, void *b);

/* AStar pathfinding algorithm. */
t_list	*get_path(t_man *man, t_cell *start, t_cell *end, int avoid_red)
{
	t_cell	*curr;
	t_list	*list;
	t_astar	a;

	a = (t_astar){end, avoid_red};
	list = init_astar(&man->map, start, end);
	curr = start;
	while (list && curr != end)
	{
		curr = list->data;
		list_del_one(&list, 0);
		if (curr->is_visited)
			continue ;
		curr->is_visited = 1;
		neighbors(man, &a, &list, curr);
	}
	list_clear(&list, 0);
	if (!end->parent)
		return (0);
	while (end != start)
	{
		list_add_front(&list, list_new(end));
		end = end->parent;
	}
	return (list);
}

static t_list	*init_astar(t_map *map, t_cell *start, t_cell *end)
{
	int	i;

	i = 0;
	while (map->cells[i].symbol)
	{
		map->cells[i].is_visited = 0;
		map->cells[i].local_goal = -1;
		map->cells[i].global_goal = -1;
		map->cells[i].parent = 0;
		map->cells[i].risk = 0;
		++i;
	}
	start->local_goal = 0;
	start->global_goal = heuristic(start, end);
	return (list_new(start));
}

static float	heuristic(t_cell *a, t_cell *b)
{
	t_vec2	pos_a;
	t_vec2	pos_b;

	set_vec2(&pos_a, a->pos.x, a->pos.y);
	set_vec2(&pos_b, b->pos.x, b->pos.y);
	return (dist_manhattan(pos_a, pos_b));
}

static void	neighbors(t_man *man, t_astar *a, t_list **list, t_cell *curr)
{
	int		i;
	t_cell	*n;
	float	goal;
	int		risk;

	i = 0;
	while (i < 4)
	{
		n = curr->neighbors[i++];
		if (!n || n->is_visited || (n != a->end && (n->is_obstacle
			|| (a->avoid_red && is_cell_an_enemy_neighbor(man, n->pos)))))
			continue ;
		goal = curr->local_goal + 1;
		risk = curr->risk + is_cell_within_enemy_reach(man, n);
		if (n->local_goal < 0 || goal < n->local_goal
			|| (goal == n->local_goal && risk < n->risk))
		{
			n->parent = curr;
			n->local_goal = goal;
			n->risk = risk;
			n->global_goal = n->local_goal + heuristic(n, a->end);
			list_add_sorted(list, list_new(n), cmp_global_goal);
		}
	}
	return ;
}

static int	cmp_global_goal(void *a, void *b)
{
	t_cell	*cell_a;
	t_cell	*cell_b;

	cell_a = (t_cell *)a;
	cell_b = (t_cell *)b;
	if (cell_a->global_goal != cell_b->global_goal)
		return ((cell_a->global_goal > cell_b->global_goal)
			- (cell_a->global_goal < cell_b->global_goal));
	return ((cell_a->risk > cell_b->risk) - (cell_a->risk < cell_b->risk));
}
