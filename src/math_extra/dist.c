#include "grim_fetcher.h"

float	dist(t_vec2 a, t_vec2 b)
{
	t_vec2	delta;

	set_vec2(&delta, a.x - b.x, a.y - b.y);
	return (sqrt_approx(delta.x * delta.x + delta.y * delta.y));
}

/* Distance along the grid, without diagonals. */
float	dist_manhattan(t_vec2 a, t_vec2 b)
{
	return (fabsf(a.x - b.x) + fabsf(a.y - b.y));
}
