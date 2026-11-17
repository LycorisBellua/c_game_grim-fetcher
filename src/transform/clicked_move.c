#include "grim_fetcher.h"

static t_list	*get_clicked_path(t_man *man);
static void		step_along_path(t_man *man);

void	move_along_clicked_path(t_man *man, long dt)
{
	static long	elapsed_time;

	if (man->click_pending)
	{
		man->clicked_path = get_clicked_path(man);
		man->click_pending = 0;
	}
	if (!man->clicked_path)
		return ;
	elapsed_time += dt;
	if (!dt)
		elapsed_time += 50;
	if (elapsed_time >= 200)
	{
		elapsed_time %= 200;
		step_along_path(man);
	}
	return ;
}

static void	step_along_path(t_man *man)
{
	t_ivec2	move;
	t_ivec2	target;

	target = ((t_cell *)man->clicked_path->data)->pos;
	set_ivec2(&move, target.x - man->player.pos.x,
		target.y - man->player.pos.y);
	if (abs(move.x) + abs(move.y) == 1)
		move_player(man, move.x, move.y);
	if (man->player.pos.x == target.x && man->player.pos.y == target.y)
		list_del_one(&man->clicked_path, 0);
	else
		list_clear(&man->clicked_path, 0);
	return ;
}

static t_list	*get_clicked_path(t_man *man)
{
	t_cell		*player_cell;
	t_cell		*cell;
	t_map_view	v;
	t_ivec2		pos;

	player_cell = find_cell_by_symbol(man->map.cells, 'P');
	get_map_view(man, &v);
	pos.x = (man->click_pos.x + v.shift.x) / get_map_zoom(man) - v.origin.x;
	pos.y = (man->click_pos.y + v.shift.y) / get_map_zoom(man) - v.origin.y;
	if (pos.x < 0 || pos.y < 0)
		return (0);
	set_ivec2(&pos, pos.x / v.cell_size.x, pos.y / v.cell_size.y);
	cell = man->map.cells;
	while (cell->symbol)
	{
		if (cell->pos.x == pos.x && cell->pos.y == pos.y
			&& (!cell->is_obstacle || cell->symbol == 'e')
			&& !is_cell_an_enemy_neighbor(man, cell->pos))
			return (get_path(man, player_cell, cell, 1));
		++cell;
	}
	return (0);
}
