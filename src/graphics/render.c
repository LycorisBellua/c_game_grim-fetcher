#include "grim_fetcher.h"

void	render(t_man *man)
{
	static t_color	c_black;
	long			dt;
	t_frame			*frame;
	t_frame			*tmp;

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
	render_map(man, tmp);
	copy_frame(frame, tmp, get_map_zoom(man));
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

void	get_map_view(t_man *man, t_ivec2 *cell_size, t_ivec2 *offset)
{
	set_ivec2(cell_size,
		man->img_ground->size.x * 3, man->img_ground->size.y * 3);
	set_ivec2(offset, man->res.res.x / cell_size->x / 2 / get_map_zoom(man),
		man->res.res.y / cell_size->y / 2 / get_map_zoom(man));
	return ;
}

int	get_map_zoom(t_man *man)
{
	return (man->zoom * man->gui_scale);
}

/* The map is drawn unscaled into `src`, then zoomed into `dst`. */
void	copy_frame(t_frame *dst, t_frame *src, int zoom_factor)
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
			src_pos.x = dst_pos.x / zoom_factor;
			src_pos.y = dst_pos.y / zoom_factor;
			color = get_frame_color(src, src_pos.x, src_pos.y);
			draw_point(dst, color, dst_pos.x, dst_pos.y);
			++dst_pos.x;
		}
		++dst_pos.y;
	}
	return ;
}
