#include "grim_fetcher.h"

static void	render_steps(t_man *man);
static void	render_collecs(t_man *man);

void	render_gui(t_man *man)
{
	render_steps(man);
	render_collecs(man);
	if (man->show_debug)
		display_fps(man);
	if (man->cursor.x >= 0 && man->cursor.y >= 0)
		draw_cursor(man, man->img_cursor, man->cursor, man->click);
	return ;
}

static void	render_steps(t_man *man)
{
	t_ivec2	pos;
	char	*text;

	set_ivec2(&pos, man->res.res.x / 2 - 20 * man->gui_scale, 0);
	draw_font(man, &pos, "Steps: ");
	text = itoa_dec(man->player.steps);
	draw_font(man, &pos, text);
	free(text);
	return ;
}

static void	render_collecs(t_man *man)
{
	t_ivec2	pos;
	char	*text;

	set_ivec2(&pos, man->res.res.x - 80 * man->gui_scale, -4 * man->gui_scale);
	draw_image(man, man->img_collec, pos);
	set_ivec2(&pos, man->res.res.x - 46 * man->gui_scale, 0);
	text = itoa_dec(man->player.collected);
	draw_font(man, &pos, text);
	free(text);
	draw_font(man, &pos, "/");
	text = itoa_dec(man->player.to_collect);
	draw_font(man, &pos, text);
	free(text);
	return ;
}
