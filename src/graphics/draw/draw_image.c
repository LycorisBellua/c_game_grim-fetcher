#include "grim_fetcher.h"

static void	draw_shadow(t_frame *frame, t_img *img, t_ivec2 pos, int scale);

void	draw_image(t_man *man, t_img *img, t_ivec2 pos)
{
	draw_image_scaled(man, img, pos, man->gui_scale);
	return ;
}

void	draw_image_scaled(t_man *man, t_img *img, t_ivec2 pos, int scale)
{
	draw_image_on_frame(&man->frame, img, pos, scale);
	return ;
}

/*
	The one loop drawing an image, used for the map (into `frame_tmp`, 
	unscaled, since the map is zoomed afterwards), images of the GUI, text and 
	the cursor.
*/
void	draw_image_on_frame(t_frame *frame, t_img *img, t_ivec2 pos, int scale)
{
	size_t	i;
	size_t	len;
	t_ivec2	p;
	t_ivec2	at;

	if (!img)
		return ;
	if (img->cycle_shadow)
		draw_shadow(frame, img, pos, scale);
	i = 0;
	len = img->size.x * img->size.y;
	while (i < len)
	{
		p.y = i / img->size.x;
		p.x = i - p.y * img->size.x;
		set_ivec2(&at, pos.x + p.x * scale, pos.y + p.y * scale);
		draw_scaled_point(frame, img->cycle[img->cycle_index][i], at, scale);
		++i;
	}
	return ;
}

/* Overwrites every pixel, without blending. */
void	fill_frame(t_frame *frame, t_color c)
{
	int	i;
	int	len;

	i = 0;
	len = frame->size.x * frame->size.y;
	while (i < len)
		frame->buf[i++] = c;
	return ;
}

static void	draw_shadow(t_frame *frame, t_img *img, t_ivec2 pos, int scale)
{
	t_img	shadow;

	shadow = *img;
	shadow.cycle = img->cycle_shadow;
	shadow.cycle_shadow = 0;
	set_ivec2(&pos, pos.x + img->shadow_offset.x * scale,
		pos.y + img->shadow_offset.y * scale);
	draw_image_on_frame(frame, &shadow, pos, scale);
	return ;
}
