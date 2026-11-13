#include "grim_fetcher.h"

static t_ivec2	get_move(t_cell *cell, unsigned int *rng);
static void		move_enemy(t_man *man, t_cell *cell, t_ivec2 move);
static void		update_enemy(t_man *man, t_cell *cell, long ms,
					unsigned int *rng);

void	move_symbol(t_map *map, t_ivec2 start, t_ivec2 end)
{
	char	symbol;
	t_img	*spr;

	symbol = map->cells[start.y * map->size.x + start.x].symbol;
	spr = map->cells[start.y * map->size.x + start.x].spr;
	map->cells[start.y * map->size.x + start.x].symbol = '0';
	map->cells[start.y * map->size.x + start.x].is_obstacle = 0;
	map->cells[start.y * map->size.x + start.x].spr = 0;
	map->cells[end.y * map->size.x + end.x].symbol = symbol;
	map->cells[end.y * map->size.x + end.x].is_obstacle = 1;
	map->cells[end.y * map->size.x + end.x].spr = spr;
	return ;
}

/*
	Cells are gone through in reading order, so an enemy that moved right or
	down would be met again in the same loop: `has_moved` keeps it at one move.
*/
void	move_enemies(t_man *man, long dt)
{
	static long			ms;
	static unsigned int	rng = 42;
	size_t				i;
	t_cell				*cell;

	ms += dt;
	rng += (unsigned int)get_time();
	i = 0;
	while (man->map.cells[i].symbol)
		man->map.cells[i++].has_moved = 0;
	i = 0;
	while (man->map.cells[i].symbol)
	{
		cell = &man->map.cells[i++];
		if ((cell->symbol == 'B' || cell->symbol == 'G') && !cell->has_moved)
			update_enemy(man, cell, ms, &rng);
	}
	if (ms >= 1000)
		ms -= 1000;
	return ;
}

/* An enemy next to the player moves onto it, otherwise it wanders. */
static void	update_enemy(t_man *man, t_cell *cell, long ms, unsigned int *rng)
{
	t_cell	*player;
	t_ivec2	pos;

	player = find_neighbor(cell, "P");
	if (player)
	{
		set_ivec2(&pos, player->pos.x - cell->pos.x,
			player->pos.y - cell->pos.y);
		move_enemy(man, cell, pos);
	}
	else if (man->player.steps && ms >= 1000)
		move_enemy(man, cell, get_move(cell, rng));
	return ;
}

static t_ivec2	get_move(t_cell *cell, unsigned int *rng)
{
	size_t	i;
	size_t	j;
	t_ivec2	allowed[4];
	t_ivec2	move;

	i = 0;
	j = 0;
	while (j < 4)
	{
		if (!cell->neighbors[j]->is_obstacle)
		{
			allowed[i].x = cell->neighbors[j]->pos.x - cell->pos.x;
			allowed[i].y = cell->neighbors[j]->pos.y - cell->pos.y;
			++i;
		}
		++j;
	}
	if (!i)
		set_ivec2(&move, 0, 0);
	else
	{
		j = rng_minmax(rng, 1, 100);
		set_ivec2(&move, allowed[j % i].x, allowed[j % i].y);
	}
	return (move);
}

static void	move_enemy(t_man *man, t_cell *cell, t_ivec2 move)
{
	t_ivec2	target;
	char	symbol;

	set_ivec2(&target, cell->pos.x + move.x, cell->pos.y + move.y);
	symbol = man->map.cells[target.y * man->map.size.x + target.x].symbol;
	if (symbol == 'P')
		change_game_state(man, GAME_STATE_FAILURE);
	else if (symbol == '0')
	{
		move_symbol(&man->map, cell->pos, target);
		man->map.cells[target.y * man->map.size.x + target.x].has_moved = 1;
	}
	return ;
}
