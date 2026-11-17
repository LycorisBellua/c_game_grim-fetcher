#include "grim_fetcher.h"

static void	draw_sprite(t_man *man, t_frame *frame, t_cell *c, t_ivec2 pos);
static void	draw_ground(t_man *man, t_frame *frame, t_ivec2 pos, t_ivec2 cell);

void	render_map(t_man *man, t_frame *frame, t_map_view *v)
{
	t_ivec2	i;
	t_ivec2	pos;
	t_cell	*c;

	pos = v->origin;
	i.y = -1;
	while (++i.y < man->map.size.y)
	{
		i.x = -1;
		while (++i.x < man->map.size.x)
		{
			c = &man->map.cells[i.y * man->map.size.x + i.x];
			if (c->symbol != '1')
				draw_ground(man, frame, pos, i);
			if (c->spr)
				draw_sprite(man, frame, c, pos);
			else if (c->symbol == '1')
				draw_walls(man, frame, pos, i);
			pos.x += v->cell_size.x;
		}
		set_ivec2(&pos, v->origin.x, pos.y + v->cell_size.y);
	}
	return ;
}

static void	draw_sprite(t_man *man, t_frame *frame, t_cell *c, t_ivec2 pos)
{
	if (c->symbol != 'E' && c->symbol != 'e')
		set_ivec2(&pos, pos.x - man->img_ground->size.x / 2,
			pos.y - man->img_ground->size.y / 2);
	draw_image_on_frame(frame, c->spr, pos, 1);
	return ;
}

static void	draw_ground(t_man *man, t_frame *frame, t_ivec2 pos, t_ivec2 cell)
{
	t_img	*img;
	t_ivec2	i;
	t_ivec2	p;

	img = man->img_ground;
	if (is_cell_an_enemy_neighbor(man, cell))
		img = man->img_red_ground;
	i.y = -1;
	while (++i.y < 3)
	{
		i.x = -1;
		while (++i.x < 3)
		{
			set_ivec2(&p, pos.x + i.x * img->size.x, pos.y + i.y * img->size.y);
			draw_image_on_frame(frame, img, p, 1);
		}
	}
	return ;
}
