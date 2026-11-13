#include "grim_fetcher.h"

static void	orient_player(t_man *man, t_cell *player, int x, int y);
static void	fetch_collec(t_man *man, t_ivec2 target);

void	move_player(t_man *man, int x, int y)
{
	t_ivec2	target;
	char	symbol;

	if (man->game_state != GAME_STATE_PLAY)
		return ;
	orient_player(man, find_cell_by_symbol(man->map.cells, 'P'), x, y);
	set_ivec2(&target, man->player.pos.x + x, man->player.pos.y + y);
	symbol = man->map.cells[target.y * man->map.size.x + target.x].symbol;
	if (symbol == 'e')
	{
		++man->player.steps;
		change_game_state(man, GAME_STATE_SUCCESS);
	}
	else if (symbol == '0' || symbol == 'C')
	{
		if (symbol == 'C')
			fetch_collec(man, target);
		move_symbol(&man->map, man->player.pos, target);
		set_ivec2(&man->player.pos, target.x, target.y);
		++man->player.steps;
	}
	return ;
}

static void	orient_player(t_man *man, t_cell *player, int x, int y)
{
	if ((x > 0 && !strcmp(player->spr->id, "dog_idle_down_left"))
		|| (y > 0 && !strcmp(player->spr->id, "dog_idle_up_right")))
		player->spr = get_image(man, "dog_idle_down_right");
	else if ((x < 0 && !strcmp(player->spr->id, "dog_idle_down_right"))
		|| (y > 0 && !strcmp(player->spr->id, "dog_idle_up_left")))
		player->spr = get_image(man, "dog_idle_down_left");
	else if ((y < 0 && !strcmp(player->spr->id, "dog_idle_down_right"))
		|| (x > 0 && !strcmp(player->spr->id, "dog_idle_up_left")))
		player->spr = get_image(man, "dog_idle_up_right");
	else if ((y < 0 && !strcmp(player->spr->id, "dog_idle_down_left"))
		|| (x < 0 && !strcmp(player->spr->id, "dog_idle_up_right")))
		player->spr = get_image(man, "dog_idle_up_left");
	return ;
}

static void	fetch_collec(t_man *man, t_ivec2 target)
{
	t_cell	*exit;

	++man->player.collected;
	man->map.cells[target.y * man->map.size.x + target.x].spr = 0;
	if (man->player.collected == man->player.to_collect)
	{
		exit = find_cell_by_symbol(man->map.cells, 'E');
		exit->symbol = 'e';
		exit->spr = get_spr_by_symbol(man, exit->symbol);
	}
	return ;
}
