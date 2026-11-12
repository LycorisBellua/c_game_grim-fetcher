#include "grim_fetcher.h"

static void    render_map(t_frame *frame);
static void    set_ivec2_vals(t_ivec2 *cs, t_ivec2 *op, t_ivec2 *p);
static t_ivec2 get_elem_pos(t_ivec2 i, t_ivec2 pos);
static void    draw_ground(t_frame *frame, t_ivec2 pos, int is_slime_neighbor);

void render(void)
{
	long    dt;
	t_frame *frame;
	t_frame *tmp;

	if (game_over_screen())
		return;
	dt = man.dt_ms;
	move_slimes(dt);
	move_along_clicked_path(dt);
	frame = man.frame[man.curr_frame];
	tmp = man.frame[2];
	clear_drawing(tmp, 0);
	clear_drawing(frame, 0);
	render_background(frame);
	render_map(tmp);
	copy_frame(frame, tmp, man.zoom);
	render_gui(frame);
	return;
}

t_img *get_spr_by_symbol(char symbol)
{
	if (symbol == 'E')
		return get_image(&man, "wall_hor_three_doorframe_closed");
	else if (symbol == 'e')
		return get_image(&man, "wall_hor_three_doorframe_open");
	else if (symbol == 'C')
		return get_image(&man, "soul_idle");
	else if (symbol == 'P')
		return get_image(&man, "dog_idle_down_right");
	else if (symbol == 'B')
		return get_image(&man, "slime_blue_idle_down_right");
	else if (symbol == 'G')
		return get_image(&man, "slime_green_idle_down_right");
	return 0;
}

static void set_ivec2_vals(t_ivec2 *cs, t_ivec2 *op, t_ivec2 *p)
{
	t_cell  *cell;
	t_ivec2 zoom_offset;

	set_ivec2(cs, man.img_ground->size.x * 3, man.img_ground->size.y * 3);
	cell = find_cell_by_symbol(man.map.cells, 'P');
	set_ivec2(&zoom_offset, 13 / man.zoom, 7 / man.zoom);
	op->x = (zoom_offset.x - cell->pos.x) * cs->x;
	op->y = (zoom_offset.y - cell->pos.y) * cs->y;
	set_ivec2(p, op->x, op->y);
	return;
}

static t_ivec2 get_elem_pos(t_ivec2 i, t_ivec2 pos)
{
	t_ivec2 p;

	set_ivec2(&p, pos.x - man.img_ground->size.x / 2,
			pos.y - man.img_ground->size.y / 2);
	if (man.map.cells[i.y * man.map.size.x + i.x].symbol == 'E'
			|| man.map.cells[i.y * man.map.size.x + i.x].symbol == 'e')
		set_ivec2(&p, pos.x, pos.y);
	return p;
}

static void render_map(t_frame *frame)
{
	t_ivec2 i;
	t_ivec2 cell_size;
	t_ivec2 origin_pos;
	t_ivec2 pos;

	set_ivec2_vals(&cell_size, &origin_pos, &pos);
	i.y = -1;
	while (++i.y < man.map.size.y)
	{
		i.x = -1;
		while (++i.x < man.map.size.x)
		{
			if (man.map.cells[i.y * man.map.size.x + i.x].symbol != '1')
				draw_ground(frame, pos, is_cell_a_slime_neighbor(i));
			if (man.map.cells[i.y * man.map.size.x + i.x].spr)
				draw_sprite(frame,
						man.map.cells[i.y * man.map.size.x + i.x].spr,
						get_elem_pos(i, pos));
			else if (man.map.cells[i.y * man.map.size.x + i.x].symbol == '1')
				draw_walls(frame, pos, i);
			pos.x += cell_size.x;
		}
		set_ivec2(&pos, origin_pos.x, pos.y + cell_size.y);
	}
	return;
}

static void draw_ground(t_frame *frame, t_ivec2 pos, int is_slime_neighbor)
{
	t_img   *img;
	t_ivec2 i;
	t_ivec2 p;

	img = is_slime_neighbor ? man.img_red_ground : man.img_ground;
	i.y = -1;
	while (++i.y < 3)
	{
		i.x = -1;
		while (++i.x < 3)
		{
			set_ivec2(&p, pos.x + i.x * img->size.x, pos.y + i.y * img->size.y);
			draw_sprite(frame, img, p);
		}
	}
	return;
}
