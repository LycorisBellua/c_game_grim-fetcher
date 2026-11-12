#include "grim_fetcher.h"

static void draw_shadow(t_frame *frame, t_img *sprite, t_ivec2 pos);
static void draw_regular(t_frame *frame, t_img *sprite, t_ivec2 pos);

/* Animations are advanced once per frame by advance_all_image_cycles(). */
void draw_sprite(t_frame *frame, t_img *sprite, t_ivec2 pos)
{
	if (!sprite)
		return;
	if (sprite->cycle_shadow)
		draw_shadow(frame, sprite, pos);
	draw_regular(frame, sprite, pos);
	return;
}

void copy_frame(t_frame *dst, t_frame *src, int zoom_factor)
{
	t_ivec2 dst_pos;
	t_ivec2 src_pos;
	t_color color;

	if (zoom_factor < 1)
		return;
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
	return;
}

static void draw_shadow(t_frame *frame, t_img *sprite, t_ivec2 pos)
{
	size_t  i;
	size_t  len;
	t_ivec2 p;

	pos.x += sprite->shadow_offset.x;
	pos.y += sprite->shadow_offset.y;
	i = 0;
	len = sprite->size.x * sprite->size.y;
	while (i < len)
	{
		p.y = i / sprite->size.x;
		p.x = i - p.y * sprite->size.x;
		set_ivec2(&p, p.x + pos.x, p.y + pos.y);
		draw_point(frame, sprite->cycle_shadow[sprite->cycle_index][i], p.x, p.y);
		++i;
	}
	return;
}

static void draw_regular(t_frame *frame, t_img *sprite, t_ivec2 pos)
{
	size_t  i;
	size_t  len;
	t_ivec2 p;

	i = 0;
	len = sprite->size.x * sprite->size.y;
	while (i < len)
	{
		p.y = i / sprite->size.x;
		p.x = i - p.y * sprite->size.x;
		set_ivec2(&p, p.x + pos.x, p.y + pos.y);
		draw_point(frame, sprite->cycle[sprite->cycle_index][i], p.x, p.y);
		++i;
	}
	return;
}
