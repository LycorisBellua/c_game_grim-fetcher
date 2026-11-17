#include "grim_fetcher.h"

void	action_toggle_vsync(t_man *man, int set)
{
	if (set)
	{
		man->vsync = !man->vsync;
		set_vsync(man);
	}
	return ;
}

void	action_toggle_fullscreen(t_man *man, int set)
{
	if (set)
		toggle_fullscreen(man);
	return ;
}

void	action_toggle_debug(t_man *man, int set)
{
	if (set)
		man->show_debug = !man->show_debug;
	return ;
}

void	action_close_window(t_man *man, int set)
{
	if (set)
		close_window_callback(man);
	return ;
}

void	action_move_to_start(t_man *man, int set)
{
	if (!set)
		return ;
	man->map_index = 0;
	if (!reload_game(man, 0))
		close_window_callback(man);
	return ;
}
