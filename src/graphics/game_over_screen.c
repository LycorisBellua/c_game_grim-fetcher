#include "grim_fetcher.h"

static void	render_victory_emote(t_man *man);
static void	render_victory_msg(t_man *man);
static void	render_reload_msg(t_man *man);
static void	draw_centered_text(t_man *man, int line, const char *msg);

int	game_over_screen(t_man *man)
{
	if (man->game_state != GAME_STATE_SUCCESS
		&& man->game_state != GAME_STATE_FAILURE)
		return (0);
	render_background(man);
	render_victory_emote(man);
	render_victory_msg(man);
	render_reload_msg(man);
	render_gui(man);
	return (1);
}

static void	render_victory_emote(t_man *man)
{
	if (man->game_state == GAME_STATE_SUCCESS)
		draw_centered_text(man, -1, "\\(^_^)/");
	else
		draw_centered_text(man, -1, "(x_x)");
	return ;
}

static void	render_victory_msg(t_man *man)
{
	if (man->game_state == GAME_STATE_SUCCESS)
		draw_centered_text(man, 0, "You won!");
	else
		draw_centered_text(man, 0, "You got killed by a slime.");
	return ;
}

static void	render_reload_msg(t_man *man)
{
	if (man->game_state == GAME_STATE_FAILURE)
		draw_centered_text(man, 1, "Press Enter to retry...");
	else if (!man->map_filenames[man->map_index + 1])
		draw_centered_text(man, 1, "Game complete!");
	else
		draw_centered_text(man, 1, "Press Enter to continue...");
	return ;
}

static void	draw_centered_text(t_man *man, int line, const char *msg)
{
	t_ivec2	pos;

	set_ivec2(&pos, man->res.res.x / 2 - (int)strlen(msg) * FONT_SIZE_X
		* man->gui_scale / 2, man->res.res.y / 2 - 4 * man->gui_scale
		+ line * 24 * man->gui_scale);
	draw_font(man, &pos, msg);
	return ;
}
