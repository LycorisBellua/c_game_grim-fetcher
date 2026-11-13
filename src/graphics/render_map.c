#include "grim_fetcher.h"

static void		set_ivec2_values(t_man *man, t_ivec2 *cs, t_ivec2 *op,
					t_ivec2 *p);
static void		draw_sprite(t_man *man, t_frame *frame, t_cell *c, t_ivec2 pos);
static void		draw_ground(t_man *man, t_frame *frame, t_ivec2 pos,
					t_ivec2 cell);

void	render_map(t_man *man, t_frame *frame)
{
	t_ivec2	i;
	t_ivec2	cell_size;
	t_ivec2	origin_pos;
	t_ivec2	pos;
	t_cell	*c;

	set_ivec2_values(man, &cell_size, &origin_pos, &pos);
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
			pos.x += cell_size.x;
		}
		set_ivec2(&pos, origin_pos.x, pos.y + cell_size.y);
	}
	return ;
}

static void	set_ivec2_values(t_man *man, t_ivec2 *cs, t_ivec2 *op, t_ivec2 *p)
{
	t_cell	*cell;
	t_ivec2	zoom_offset;

	cell = find_cell_by_symbol(man->map.cells, 'P');
	get_map_view(man, cs, &zoom_offset);
	op->x = (zoom_offset.x - cell->pos.x) * cs->x;
	op->y = (zoom_offset.y - cell->pos.y) * cs->y;
	set_ivec2(p, op->x, op->y);
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
