#include "grim_fetcher.h"

static void	draw_top_walls(t_man *man, t_frame *f, t_ivec2 p, t_ivec2 i);
static void	draw_top_walls_bis(t_man *man, t_frame *f, t_ivec2 p, t_ivec2 i);
static void	draw_lat_walls(t_man *man, t_frame *f, t_ivec2 p, t_ivec2 i);
static void	draw_bot_walls(t_man *man, t_frame *f, t_ivec2 p, t_ivec2 i);

void	draw_walls(t_man *man, t_frame *frame, t_ivec2 pos, t_ivec2 i)
{
	draw_top_walls(man, frame, pos, i);
	draw_top_walls_bis(man, frame, pos, i);
	draw_lat_walls(man, frame, pos, i);
	draw_bot_walls(man, frame, pos, i);
	return ;
}

static void	draw_top_walls(t_man *man, t_frame *f, t_ivec2 p, t_ivec2 i)
{
	t_img	*cliff;
	t_ivec2	pd;

	cliff = man->img_wall_hor_one_cliff;
	if (i.y > 0 && !is_wall(&man->map, i.x, i.y - 1))
	{
		set_ivec2(&pd, p.x, p.y + cliff->size.y);
		draw_image_on_frame(f, cliff, pd, 1);
		set_ivec2(&pd, pd.x + cliff->size.x, pd.y);
		draw_image_on_frame(f, cliff, pd, 1);
		set_ivec2(&pd, pd.x + cliff->size.x, pd.y);
		draw_image_on_frame(f, cliff, pd, 1);
		draw_image_on_frame(f, man->img_wall_hor_three, p, 1);
	}
	if (i.y > 0 && is_wall(&man->map, i.x, i.y - 1)
		&& i.x > 0 && is_wall(&man->map, i.x - 1, i.y)
		&& !is_wall(&man->map, i.x - 1, i.y - 1))
	{
		set_ivec2(&pd, p.x, p.y + cliff->size.y);
		draw_image_on_frame(f, cliff, pd, 1);
		draw_image_on_frame(f, man->img_wall_hor_one, p, 1);
	}
	return ;
}

static void	draw_top_walls_bis(t_man *man, t_frame *f, t_ivec2 p, t_ivec2 i)
{
	t_ivec2	pd;
	t_ivec2	pp;

	set_ivec2(&pp, p.x + man->img_wall_hor_one->size.x * 2, p.y);
	if (i.y > 0 && is_wall(&man->map, i.x, i.y - 1)
		&& i.x < man->map.size.x - 1 && is_wall(&man->map, i.x + 1, i.y)
		&& !is_wall(&man->map, i.x + 1, i.y - 1))
	{
		set_ivec2(&pd, p.x + man->img_wall_hor_one_cliff->size.x * 2,
			p.y + man->img_wall_hor_one_cliff->size.y);
		draw_image_on_frame(f, man->img_wall_hor_one_cliff, pd, 1);
		draw_image_on_frame(f, man->img_wall_hor_one, pp, 1);
	}
	return ;
}

static void	draw_lat_walls(t_man *man, t_frame *f, t_ivec2 p, t_ivec2 i)
{
	if (i.x > 0 && !is_wall(&man->map, i.x - 1, i.y))
		draw_image_on_frame(f, man->img_wall_ver_two, p, 1);
	set_ivec2(&p, p.x + man->img_wall_ver_two->size.x * 2, p.y);
	if (i.x < man->map.size.x - 1 && !is_wall(&man->map, i.x + 1, i.y))
		draw_image_on_frame(f, man->img_wall_ver_two, p, 1);
	return ;
}

static void	draw_bot_walls(t_man *man, t_frame *f, t_ivec2 p, t_ivec2 i)
{
	int	below;

	if ((i.y + 1) * man->map.size.x + i.x >= man->map.size.x * man->map.size.y)
		return ;
	below = is_wall(&man->map, i.x, i.y + 1);
	p.y += man->img_wall_hor_three->size.y / 2;
	if (i.y < man->map.size.y - 1 && !below)
		draw_image_on_frame(f, man->img_wall_hor_three, p, 1);
	if (i.y < man->map.size.y - 1 && below
		&& i.x > 0 && is_wall(&man->map, i.x - 1, i.y)
		&& !is_wall(&man->map, i.x - 1, i.y + 1))
	{
		draw_image_on_frame(f, man->img_wall_hor_one, p, 1);
		draw_image_on_frame(f, man->img_wall_ver_two, p, 1);
	}
	p.x += man->img_wall_hor_one->size.x * 2;
	if (i.y < man->map.size.y - 1 && below
		&& i.x < man->map.size.x - 1 && is_wall(&man->map, i.x + 1, i.y)
		&& !is_wall(&man->map, i.x + 1, i.y + 1))
	{
		draw_image_on_frame(f, man->img_wall_hor_one, p, 1);
		draw_image_on_frame(f, man->img_wall_ver_two, p, 1);
	}
	return ;
}
