#include "grim_fetcher.h"

int	add_red_version_of_ground(t_man *man)
{
	size_t	i;
	size_t	len;

	man->img_red_ground = duplicate_image(ID_RED_GROUND, man->img_ground);
	if (!man->img_red_ground)
		return (put_error(E_FAIL_MEM, 0, 0));
	len = man->img_red_ground->size.x * man->img_red_ground->size.y;
	i = 0;
	while (i < len)
	{
		man->img_red_ground->cycle[0][i].r = 255;
		++i;
	}
	return (1);
}

int	is_cell_an_enemy_neighbor(t_man *man, t_ivec2 i)
{
	t_cell	*cell;

	cell = &man->map.cells[i.y * man->map.size.x + i.x];
	if (cell->symbol == 'E' || cell->symbol == 'e')
		return (0);
	return (find_neighbor(cell, "BG") != 0);
}

t_cell	*find_neighbor(t_cell *cell, const char *symbols)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cell->neighbors[i] && cell->neighbors[i]->symbol && strchr(symbols,
			cell->neighbors[i]->symbol))
			return (cell->neighbors[i]);
		++i;
	}
	return (0);
}
