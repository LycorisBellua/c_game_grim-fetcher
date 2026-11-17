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
	char	*collected;
	char	*to_collect;
	int		offset;

	collected = itoa_dec(man->player.collected);
	to_collect = itoa_dec(man->player.to_collect);
	offset = 0;
	if (collected && to_collect)
		offset = FONT_SIZE_X * (int)(strlen(collected) + 1 + strlen(to_collect))
			+ FONT_PAD + 1;
	if (offset < 46)
		offset = 46;
	set_ivec2(&pos, man->res.res.x - (offset + 34) * man->gui_scale,
		-4 * man->gui_scale);
	draw_image(man, man->img_collec, pos);
	set_ivec2(&pos, man->res.res.x - offset * man->gui_scale, 0);
	draw_font(man, &pos, collected);
	draw_font(man, &pos, "/");
	draw_font(man, &pos, to_collect);
	free(collected);
	free(to_collect);
	return ;
}
