#include "grim_fetcher.h"

void	action_move_up(t_man *man, int set)
{
	if (set)
		move_player(man, 0, -1);
	return ;
}

void	action_move_down(t_man *man, int set)
{
	if (set)
		move_player(man, 0, 1);
	return ;
}

void	action_move_left(t_man *man, int set)
{
	if (set)
		move_player(man, -1, 0);
	return ;
}

void	action_move_right(t_man *man, int set)
{
	if (set)
		move_player(man, 1, 0);
	return ;
}
