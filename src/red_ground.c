#include "grim_fetcher.h"

int add_red_version_of_ground(void)
{
	size_t i;
	size_t len;

	man.img_red_ground = duplicate_image(ID_RED_GROUND, man.img_ground);
	if (!man.img_red_ground)
		return put_error(E_FAIL_MEM, 0, 0);
	len = man.img_red_ground->size.x * man.img_red_ground->size.y;
	i = 0;
	while (i < len)
	{
		man.img_red_ground->cycle[0][i].r = 255;
		++i;
	}
	return 1;
}

int is_cell_a_slime_neighbor(t_ivec2 i)
{
	t_ivec2 size;
	t_cell  *cells;

	set_ivec2(&size, man.map.size.x, man.map.size.y);
	cells = man.map.cells;
	if (cells[i.y * size.x + i.x].symbol == 'E'
			|| cells[i.y * size.x + i.x].symbol == 'e')
		return 0;
	else if (i.y > 0 && (cells[(i.y - 1) * size.x + i.x].symbol == 'B'
				|| cells[(i.y - 1) * size.x + i.x].symbol == 'G'))
		return 1;
	else if (i.y < size.y && (cells[(i.y + 1) * size.x + i.x].symbol == 'B'
				|| cells[(i.y + 1) * size.x + i.x].symbol == 'G'))
		return 1;
	else if (i.x > 0 && (cells[i.y * size.x + (i.x - 1)].symbol == 'B'
				|| cells[i.y * size.x + (i.x - 1)].symbol == 'G'))
		return 1;
	else if (i.x < size.x && (cells[i.y * size.x + (i.x + 1)].symbol == 'B'
				|| cells[i.y * size.x + (i.x + 1)].symbol == 'G'))
		return 1;
	return 0;
}
