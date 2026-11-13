#include "grim_fetcher.h"

void	cancel_keys_in_game_state(t_man *man)
{
	int	i;

	i = 0;
	while (man->keys[i].keycode)
	{
		if (man->keys[i].state != KEY_STATE_NONE)
			execute_input_action(man, man->keys[i].keycode, KEY_STATE_NONE);
		++i;
	}
	return ;
}

void	change_game_state(t_man *man, t_game_state new_state)
{
	cancel_keys_in_game_state(man);
	man->game_state = new_state;
	return ;
}

void	action_continue(t_man *man, int set)
{
	if (set && !reload_game(man, man->game_state == GAME_STATE_SUCCESS))
		close_window_callback(man);
	return ;
}
