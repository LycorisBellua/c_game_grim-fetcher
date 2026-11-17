#include "grim_fetcher.h"

void	render(t_man *man)
{
	static t_color	c_black;
	long			dt;
	t_frame			*frame;
	t_frame			*tmp;
	t_map_view		view;

	if (game_over_screen(man))
		return ;
	dt = man->dt_ms;
	move_enemies(man, dt);
	move_along_clicked_path(man, dt);
	frame = &man->frame;
	tmp = &man->frame_tmp;
	fill_frame(tmp, c_black);
	fill_frame(frame, c_black);
	render_background(man);
	get_map_view(man, &view);
	render_map(man, tmp, &view);
	copy_frame(frame, tmp, get_map_zoom(man), view.shift);
	render_gui(man);
	return ;
}

t_img	*get_spr_by_symbol(t_man *man, char symbol)
{
	if (symbol == 'E')
		return (get_image(man, "wall_hor_three_doorframe_closed"));
	else if (symbol == 'e')
		return (get_image(man, "wall_hor_three_doorframe_open"));
	else if (symbol == 'C')
		return (get_image(man, "soul_idle"));
	else if (symbol == 'P')
		return (get_image(man, "dog_idle_down_right"));
	else if (symbol == 'B')
		return (get_image(man, "slime_blue_idle_down_right"));
	else if (symbol == 'G')
		return (get_image(man, "slime_green_idle_down_right"));
	return (0);
}

/*
	A map cell is 3x3 ground tiles. In the unzoomed frame, the center of the
	player's cell is drawn at `center`, which, once zoomed, is `shift` pixels
	past the middle of the screen: shifting the zoomed frame back by that much
	keeps the player exactly in the middle, at every zoom.
*/
void	get_map_view(t_man *man, t_map_view *v)
{
	t_cell	*player;
	t_ivec2	center;
	int		zoom;

	zoom = get_map_zoom(man);
	set_ivec2(&v->cell_size, man->img_ground->size.x * 3,
		man->img_ground->size.y * 3);
	set_ivec2(&center, (man->res.res.x / 2 + zoom - 1) / zoom,
		(man->res.res.y / 2 + zoom - 1) / zoom);
	set_ivec2(&v->shift, center.x * zoom - man->res.res.x / 2,
		center.y * zoom - man->res.res.y / 2);
	player = find_cell_by_symbol(man->map.cells, 'P');
	set_ivec2(&v->origin,
		center.x - player->pos.x * v->cell_size.x - v->cell_size.x / 2,
		center.y - player->pos.y * v->cell_size.y - v->cell_size.y / 2);
	return ;
}

int	get_map_zoom(t_man *man)
{
	return (man->zoom * man->gui_scale);
}

/* The map is drawn unscaled into `src`, then zoomed into `dst`. */
void	copy_frame(t_frame *dst, t_frame *src, int zoom_factor, t_ivec2 shift)
{
	t_ivec2	dst_pos;
	t_ivec2	src_pos;
	t_color	color;

	if (zoom_factor < 1)
		return ;
	dst_pos.y = 0;
	while (dst_pos.y < dst->size.y)
	{
		dst_pos.x = 0;
		while (dst_pos.x < dst->size.x)
		{
			src_pos.x = (dst_pos.x + shift.x) / zoom_factor;
			src_pos.y = (dst_pos.y + shift.y) / zoom_factor;
			color = get_frame_color(src, src_pos.x, src_pos.y);
			draw_point(dst, color, dst_pos.x, dst_pos.y);
			++dst_pos.x;
		}
		++dst_pos.y;
	}
	return ;
}
