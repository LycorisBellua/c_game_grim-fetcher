#include "grim_fetcher.h"

void	draw_point(t_frame *f, t_color c, int x, int y)
{
	t_color	*buf;

	if (x < 0 || y < 0 || x >= f->size.x || y >= f->size.y)
		return ;
	buf = f->buf + (y * f->size.x + x);
	if (c.a < 255)
		c = alpha_blending(*buf, c);
	*buf = c;
	return ;
}

/* Draws one source pixel as a scale x scale block, for the GUI scale. */
void	draw_scaled_point(t_frame *f, t_color c, t_ivec2 at, int scale)
{
	int	bx;
	int	by;

	by = -1;
	while (++by < scale)
	{
		bx = -1;
		while (++bx < scale)
			draw_point(f, c, at.x + bx, at.y + by);
	}
	return ;
}
