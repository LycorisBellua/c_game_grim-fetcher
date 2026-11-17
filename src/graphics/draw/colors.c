#include "grim_fetcher.h"

t_color	get_color_rgba(t_ubyte r, t_ubyte g, t_ubyte b, t_ubyte a)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return (c);
}

t_color	alpha_blending(t_color prev, t_color new)
{
	t_color	blend;

	if (new.a == 0)
		return (prev);
	if (prev.a == 255)
	{
		blend.a = 255;
		blend.r = (new.a * new.r + (255 - new.a) * prev.r) / 255;
		blend.g = (new.a * new.g + (255 - new.a) * prev.g) / 255;
		blend.b = (new.a * new.b + (255 - new.a) * prev.b) / 255;
		return (blend);
	}
	blend.a = new.a + (255 - new.a) * prev.a / 255;
	if (!blend.a)
		return (get_color_rgba(0, 0, 0, 0));
	blend.r = (new.a * new.r + (255 - new.a) * prev.a * prev.r / 255) / blend.a;
	blend.g = (new.a * new.g + (255 - new.a) * prev.a * prev.g / 255) / blend.a;
	blend.b = (new.a * new.b + (255 - new.a) * prev.a * prev.b / 255) / blend.a;
	return (blend);
}

t_color	get_frame_color(t_frame *f, int x, int y)
{
	return (f->buf[y * f->size.x + x]);
}
